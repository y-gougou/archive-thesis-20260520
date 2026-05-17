import torch
import torch.nn as nn

from .cwcnn_fa_baseline import FALayer
from .sage_cnn import SourceDynamicFusion, conv_block, temporal_difference


class SAGECNNVariant(nn.Module):
    """Configurable SAGE-CNN variant for module-level ablation experiments."""

    def __init__(
        self,
        input_channels=15,
        num_classes=4,
        use_diff=True,
        use_saf=True,
        diff_orders=(1, 2),
        dropout=0.0,
    ):
        super().__init__()
        if input_channels != 15:
            raise ValueError("SAGE-CNN ablations expect the fixed 15-channel feature order.")

        self.diff_orders = tuple(diff_orders) if use_diff else ()
        enhanced_channels = input_channels * (1 + len(self.diff_orders))
        self.project = (
            nn.Sequential(
                nn.Conv1d(enhanced_channels, input_channels, kernel_size=1, bias=False),
                nn.BatchNorm1d(input_channels),
                nn.ReLU(inplace=True),
            )
            if use_diff
            else nn.Identity()
        )
        self.source_fusion = SourceDynamicFusion(hidden=8) if use_saf else nn.Identity()
        self.conv1 = conv_block(input_channels, kernel_size=7, padding=3)
        self.fa = FALayer(input_channels, hidden=8)
        self.conv2 = conv_block(input_channels, kernel_size=3, padding=1)
        self.conv3 = conv_block(input_channels, kernel_size=3, padding=1)
        self.conv4 = conv_block(input_channels, kernel_size=3, padding=1)
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

    def forward(self, x):
        x = self.project(self.enhance(x))
        x = self.source_fusion(x)
        x = self.conv1(x)
        x = self.fa(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        x = self.pool(x).squeeze(-1)
        return self.classifier(x)

class SAGECNNNoDiffGate(SAGECNNVariant):
    """Ablation: remove temporal-difference enhancement and source-aware fusion."""

    def __init__(self, input_channels=15, num_classes=4, dropout=0.0):
        super().__init__(
            input_channels=input_channels,
            num_classes=num_classes,
            use_diff=False,
            use_saf=False,
            dropout=dropout,
        )


class SAGECNNNoDiff(SAGECNNVariant):
    """Ablation: remove temporal-difference enhancement only."""

    def __init__(self, input_channels=15, num_classes=4, dropout=0.0):
        super().__init__(
            input_channels=input_channels,
            num_classes=num_classes,
            use_diff=False,
            use_saf=True,
            dropout=dropout,
        )


class SAGECNNNoSAF(SAGECNNVariant):
    """Ablation: remove source-aware fusion only."""

    def __init__(self, input_channels=15, num_classes=4, dropout=0.0):
        super().__init__(
            input_channels=input_channels,
            num_classes=num_classes,
            use_diff=True,
            use_saf=False,
            dropout=dropout,
        )


def build_ablation_model(model_name, input_channels=15, num_classes=4, dropout=0.0):
    if model_name == "sage_no_diff_gate":
        return SAGECNNNoDiffGate(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    if model_name == "sage_no_diff":
        return SAGECNNNoDiff(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    if model_name == "sage_no_saf":
        return SAGECNNNoSAF(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    raise ValueError(f"Unknown SAGE-CNN ablation model name: {model_name}")
