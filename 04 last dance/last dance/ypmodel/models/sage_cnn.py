import torch
import torch.nn as nn
import torch.nn.functional as F

from .cwcnn_fa_baseline import FALayer


SOURCE_SLICES = {
    "odom": slice(0, 3),
    "wheel": slice(3, 6),
    "imu": slice(6, 12),
    "current": slice(12, 15),
}


def temporal_difference(x, order):
    if order == 1:
        diff = x[:, :, 1:] - x[:, :, :-1]
        return F.pad(diff, (1, 0), mode="constant", value=0.0)
    if order == 2:
        diff = x[:, :, 2:] - 2.0 * x[:, :, 1:-1] + x[:, :, :-2]
        return F.pad(diff, (2, 0), mode="constant", value=0.0)
    raise ValueError("temporal_difference currently supports order 1 or 2.")


class SourceDynamicFusion(nn.Module):
    """Learn source-level fusion weights from temporal statistics."""

    def __init__(self, hidden=8):
        super().__init__()
        self.source_names = tuple(SOURCE_SLICES.keys())
        self.scorer = nn.Sequential(
            nn.Linear(3, hidden),
            nn.Tanh(),
            nn.Linear(hidden, 1),
        )
        self.last_weights = None

    def forward(self, x):
        source_context = []
        for name in self.source_names:
            source_x = x[:, SOURCE_SLICES[name], :]
            mean_abs = source_x.abs().mean(dim=(1, 2))
            std = source_x.std(dim=(1, 2), unbiased=False)
            diff_abs = temporal_difference(source_x, 1).abs().mean(dim=(1, 2))
            source_context.append(torch.stack([mean_abs, std, diff_abs], dim=1))

        context = torch.stack(source_context, dim=1)
        scores = self.scorer(context).squeeze(-1)
        weights = torch.softmax(scores, dim=1)
        if not torch.onnx.is_in_onnx_export():
            self.last_weights = weights.detach()

        fused_sources = []
        for index, name in enumerate(self.source_names):
            source_x = x[:, SOURCE_SLICES[name], :]
            scale = weights[:, index].view(-1, 1, 1) * len(self.source_names)
            fused_sources.append(source_x * scale)
        return torch.cat(fused_sources, dim=1)


def conv_block(channels, kernel_size, padding):
    return nn.Sequential(
        nn.Conv1d(
            channels,
            channels,
            kernel_size=kernel_size,
            stride=1,
            padding=padding,
            groups=1,
        ),
        nn.BatchNorm1d(channels),
        nn.ReLU(inplace=True),
    )


class SAGECNN(nn.Module):
    """Source-Aware Gradient-Enhanced CNN.

    SAGE-CNN combines temporal difference projection, source-aware gated
    fusion, FA recalibration, and standard Conv1d blocks for multi-sensor
    robot fault diagnosis.
    """

    def __init__(
        self,
        input_channels=15,
        num_classes=4,
        diff_orders=(1, 2),
        conv_layers=4,
        fa_position=1,
        dropout=0.0,
    ):
        super().__init__()
        if input_channels != 15:
            raise ValueError("SAGE-CNN expects the fixed 15-channel feature order.")
        if conv_layers < 1:
            raise ValueError("SAGE-CNN expects at least one Conv1d layer.")
        if fa_position < 0 or fa_position > conv_layers:
            raise ValueError("FA position must be between 0 and conv_layers.")

        self.diff_orders = tuple(diff_orders)
        self.conv_layers = int(conv_layers)
        self.fa_position = int(fa_position)
        enhanced_channels = input_channels * (1 + len(self.diff_orders))
        self.project = nn.Sequential(
            nn.Conv1d(enhanced_channels, input_channels, kernel_size=1, bias=False),
            nn.BatchNorm1d(input_channels),
            nn.ReLU(inplace=True),
        )
        self.source_fusion = SourceDynamicFusion(hidden=8)
        conv_blocks = [conv_block(input_channels, kernel_size=7, padding=3)]
        conv_blocks.extend(
            conv_block(input_channels, kernel_size=3, padding=1)
            for _ in range(self.conv_layers - 1)
        )
        self.convs = nn.ModuleList(conv_blocks)
        self.fa = FALayer(input_channels, hidden=8)
        self.pool = nn.AdaptiveAvgPool1d(1)
        self.classifier = nn.Sequential(
            nn.Linear(input_channels, input_channels * 4),
            nn.ReLU(inplace=True),
            nn.Dropout(float(dropout)) if dropout > 0 else nn.Identity(),
            nn.Linear(input_channels * 4, num_classes),
        )

    def enhance(self, x):
        features = [x]
        features.extend(temporal_difference(x, order) for order in self.diff_orders)
        return torch.cat(features, dim=1)

    def forward(self, x, return_source_weights=False):
        x = self.project(self.enhance(x))
        x = self.source_fusion(x)
        if self.fa_position == 0:
            x = self.fa(x)
        for index, conv in enumerate(self.convs, start=1):
            x = conv(x)
            if self.fa_position == index:
                x = self.fa(x)
        x = self.pool(x).squeeze(-1)
        logits = self.classifier(x)
        if return_source_weights:
            return logits, self.get_source_weights()
        return logits

    def get_source_weights(self):
        return self.source_fusion.last_weights
