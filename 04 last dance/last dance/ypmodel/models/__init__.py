from .comparison_models import LSTMClassifier, MLPClassifier, NormalCNN1D
from .cwcnn_fa_baseline import CWCNNFABaseline
from .sage_cnn import SAGECNN
from .sage_cnn_ablation import build_ablation_model


def build_model(model_name, input_channels=15, num_classes=4, dropout=0.0):
    if model_name in {"baseline", "sage_cnn"}:
        return SAGECNN(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    if model_name.startswith("sage_depth_"):
        conv_layers = int(model_name.rsplit("_", 1)[1])
        return SAGECNN(
            input_channels=input_channels,
            num_classes=num_classes,
            conv_layers=conv_layers,
            dropout=dropout,
        )
    if model_name.startswith("sage_fa_pos_"):
        fa_position = int(model_name.rsplit("_", 1)[1])
        return SAGECNN(
            input_channels=input_channels,
            num_classes=num_classes,
            fa_position=fa_position,
            dropout=dropout,
        )
    if model_name == "cwcnn_fa":
        return CWCNNFABaseline(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    if model_name == "normal_cnn":
        return NormalCNN1D(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    if model_name == "mlp":
        return MLPClassifier(input_channels=input_channels, num_classes=num_classes, dropout=dropout if dropout > 0 else 0.2)
    if model_name == "lstm":
        return LSTMClassifier(input_channels=input_channels, num_classes=num_classes, dropout=dropout)
    if model_name == "bilstm":
        return LSTMClassifier(input_channels=input_channels, num_classes=num_classes, bidirectional=True, dropout=dropout)
    return build_ablation_model(model_name, input_channels=input_channels, num_classes=num_classes, dropout=dropout)
