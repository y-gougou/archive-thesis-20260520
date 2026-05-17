import torch
import torch.nn as nn


class NormalCNN1D(nn.Module):
    """Standard 1D CNN over concatenated sensor channels."""

    def __init__(self, input_channels=15, num_classes=4, dropout=0.0):
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv1d(input_channels, 32, kernel_size=7, padding=3),
            nn.BatchNorm1d(32),
            nn.ReLU(inplace=True),
            nn.Conv1d(32, 64, kernel_size=5, padding=2),
            nn.BatchNorm1d(64),
            nn.ReLU(inplace=True),
            nn.Conv1d(64, 64, kernel_size=3, padding=1),
            nn.BatchNorm1d(64),
            nn.ReLU(inplace=True),
            nn.AdaptiveAvgPool1d(1),
        )
        self.classifier = nn.Sequential(
            nn.Linear(64, 64),
            nn.ReLU(inplace=True),
            nn.Dropout(float(dropout)) if dropout > 0 else nn.Identity(),
            nn.Linear(64, num_classes),
        )

    def forward(self, x):
        x = self.features(x).squeeze(-1)
        return self.classifier(x)


class MLPClassifier(nn.Module):
    """Flattened-window multilayer perceptron baseline."""

    def __init__(self, input_channels=15, num_classes=4, window_size=50, dropout=0.2):
        super().__init__()
        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(input_channels * window_size, 256),
            nn.BatchNorm1d(256),
            nn.ReLU(inplace=True),
            nn.Dropout(float(dropout)),
            nn.Linear(256, 128),
            nn.BatchNorm1d(128),
            nn.ReLU(inplace=True),
            nn.Dropout(float(dropout)),
            nn.Linear(128, num_classes),
        )

    def forward(self, x):
        return self.classifier(x)


class LSTMClassifier(nn.Module):
    """LSTM/BiLSTM baseline over the time-major multi-sensor sequence."""

    def __init__(
        self,
        input_channels=15,
        num_classes=4,
        hidden_size=64,
        num_layers=1,
        bidirectional=False,
        dropout=0.0,
    ):
        super().__init__()
        self.lstm = nn.LSTM(
            input_size=input_channels,
            hidden_size=hidden_size,
            num_layers=num_layers,
            batch_first=True,
            bidirectional=bidirectional,
        )
        out_features = hidden_size * (2 if bidirectional else 1)
        self.classifier = nn.Sequential(
            nn.Linear(out_features, out_features),
            nn.ReLU(inplace=True),
            nn.Dropout(float(dropout)) if dropout > 0 else nn.Identity(),
            nn.Linear(out_features, num_classes),
        )
        self.input_transpose_log = "input_transpose: [N,15,50] -> [N,50,15]"

    def forward(self, x):
        x = x.transpose(1, 2)
        _, (hidden, _) = self.lstm(x)
        if self.lstm.bidirectional:
            features = torch.cat([hidden[-2], hidden[-1]], dim=1)
        else:
            features = hidden[-1]
        return self.classifier(features)
