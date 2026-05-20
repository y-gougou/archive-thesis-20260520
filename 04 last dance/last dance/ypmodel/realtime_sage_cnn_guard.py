import argparse
import csv
import json
from collections import Counter, deque
from dataclasses import asdict, dataclass
from pathlib import Path

import joblib
import numpy as np
import torch
import torch.nn.functional as F

from models import build_model


LABEL_NAMES = {
    0: "normal",
    1: "wheel_slip",
    2: "drive_abnormal",
    3: "shaft_eccentricity",
}

FEATURE_NAMES = [
    "odom_vx",
    "odom_vy",
    "odom_wz",
    "wheel_speed0",
    "wheel_speed1",
    "wheel_speed2",
    "imu_ax",
    "imu_ay",
    "imu_az",
    "imu_gx",
    "imu_gy",
    "imu_gz",
    "current0",
    "current1",
    "current2",
]


@dataclass
class GuardConfig:
    checkpoint_path: str = "selected_sage_cnn_model/sage_cnn_selected_best_model.pth"
    scaler_path: str = "selected_sage_cnn_model/strict_scaler.pkl"
    window_size: int = 50
    input_channels: int = 15
    static_linear_speed_threshold: float = 0.08
    static_angular_speed_threshold: float = 0.08
    static_wheel_speed_threshold: float = 0.08
    static_required_windows: int = 5
    vote_window_size: int = 5
    vote_required_count: int = 3
    low_confidence_threshold: float = 0.70
    margin_threshold: float = 0.15
    static_display_label: str = "normal_static"
    static_report_label: str = "normal"
    ambiguous_pair_hold_enabled: bool = True


def reshape_for_scaler(x):
    return x.transpose(0, 2, 1).reshape(-1, x.shape[1])


def transform_with_scaler(x, scaler):
    n, c, t = x.shape
    flat = reshape_for_scaler(x)
    scaled = scaler.transform(flat).reshape(n, t, c).transpose(0, 2, 1)
    return scaled.astype(np.float32)


def _mean_abs(window, channel_slice):
    return float(np.mean(np.abs(window[channel_slice, :])))


class SAGECNNRealtimeGuard:
    """Deployment guard for SAGE-CNN real-time robot fault diagnosis.

    The guard handles two practical deployment issues without changing the
    trained SAGE-CNN: static-state gating before inference, and temporal
    stabilization after inference.
    """

    def __init__(self, config=None, device=None):
        self.config = config or GuardConfig()
        self.device = torch.device(device or ("cuda" if torch.cuda.is_available() else "cpu"))
        self.model = self._load_model()
        self.scaler = joblib.load(self.config.scaler_path)
        self.static_history = deque(maxlen=self.config.static_required_windows)
        self.pred_history = deque(maxlen=self.config.vote_window_size)
        self.stable_label = None
        self.stable_prob = 0.0
        self.last_result = None

    @classmethod
    def from_config_file(cls, path, device=None):
        data = json.loads(Path(path).read_text(encoding="utf-8"))
        return cls(GuardConfig(**data), device=device)

    def _load_model(self):
        checkpoint = torch.load(self.config.checkpoint_path, map_location=self.device, weights_only=False)
        model = build_model("sage_no_saf", input_channels=self.config.input_channels, num_classes=4)
        model.load_state_dict(checkpoint["model_state_dict"], strict=True)
        model.to(self.device)
        model.eval()
        return model

    def reset(self):
        self.static_history.clear()
        self.pred_history.clear()
        self.stable_label = None
        self.stable_prob = 0.0
        self.last_result = None

    def motion_stats(self, raw_window):
        odom_vx = raw_window[0, :]
        odom_vy = raw_window[1, :]
        odom_wz = raw_window[2, :]
        linear_speed = np.sqrt(odom_vx ** 2 + odom_vy ** 2)
        return {
            "linear_speed_mean": float(np.mean(np.abs(linear_speed))),
            "linear_speed_max": float(np.max(np.abs(linear_speed))),
            "angular_speed_mean": float(np.mean(np.abs(odom_wz))),
            "angular_speed_max": float(np.max(np.abs(odom_wz))),
            "wheel_speed_mean_abs": _mean_abs(raw_window, slice(3, 6)),
            "wheel_speed_max_abs": float(np.max(np.abs(raw_window[3:6, :]))),
        }

    def is_static_window(self, raw_window):
        stats = self.motion_stats(raw_window)
        is_static = (
            stats["linear_speed_mean"] < self.config.static_linear_speed_threshold
            and stats["angular_speed_mean"] < self.config.static_angular_speed_threshold
            and stats["wheel_speed_mean_abs"] < self.config.static_wheel_speed_threshold
        )
        return bool(is_static), stats

    def preprocess_window(self, raw_window):
        raw_window = np.asarray(raw_window, dtype=np.float32)
        self._check_window_shape(raw_window)
        return transform_with_scaler(raw_window[None, :, :], self.scaler)

    def predict_window(self, raw_window, already_scaled=False):
        raw_window = np.asarray(raw_window, dtype=np.float32)
        self._check_window_shape(raw_window)

        is_static, stats = self.is_static_window(raw_window)
        self.static_history.append(is_static)
        static_confirmed = (
            len(self.static_history) == self.config.static_required_windows
            and all(self.static_history)
        )
        if static_confirmed:
            result = self._static_result(stats)
            self.last_result = result
            return result

        if already_scaled:
            model_input = raw_window[None, :, :].astype(np.float32)
        else:
            model_input = self.preprocess_window(raw_window)

        with torch.no_grad():
            batch = torch.from_numpy(model_input).float().to(self.device)
            logits = self.model(batch)
            probs = F.softmax(logits, dim=1)[0].detach().cpu().numpy()
        result = self.update_from_probabilities(probs, motion_stats=stats, is_static=False)
        self.last_result = result
        return result

    def update_from_probabilities(self, probs, motion_stats=None, is_static=False):
        probs = np.asarray(probs, dtype=np.float64)
        if probs.shape != (4,):
            raise ValueError(f"Expected probability vector with shape (4,), got {probs.shape}")
        order = np.argsort(probs)[::-1]
        top1 = int(order[0])
        top2 = int(order[1])
        top1_prob = float(probs[top1])
        top2_prob = float(probs[top2])
        margin = top1_prob - top2_prob
        is_low_confidence = (
            top1_prob < self.config.low_confidence_threshold
            or margin < self.config.margin_threshold
        )
        ambiguous = self._is_ambiguous_slip_eccentricity(top1, top2, margin)

        raw_label = LABEL_NAMES[top1]
        candidate_label = raw_label
        stable_label = self.stable_label or candidate_label
        stable_prob = self.stable_prob or top1_prob

        if ambiguous and self.config.ambiguous_pair_hold_enabled and self.stable_label is not None:
            stable_label = self.stable_label
            stable_prob = self.stable_prob
        elif not is_low_confidence:
            self.pred_history.append((candidate_label, top1_prob))
            vote_label, vote_count = Counter(label for label, _ in self.pred_history).most_common(1)[0]
            if vote_count >= self.config.vote_required_count:
                stable_label = vote_label
                stable_prob = self._mean_prob_for_label(vote_label)
                self.stable_label = stable_label
                self.stable_prob = stable_prob
        elif self.stable_label is None:
            self.pred_history.append((candidate_label, top1_prob))
            self.stable_label = stable_label
            self.stable_prob = stable_prob

        return {
            "raw_model_label": raw_label,
            "raw_model_prob": top1_prob,
            "stable_label": stable_label,
            "stable_prob": float(stable_prob),
            "is_static": bool(is_static),
            "is_low_confidence": bool(is_low_confidence),
            "ambiguous_slip_eccentricity": bool(ambiguous),
            "top2_labels": [LABEL_NAMES[top1], LABEL_NAMES[top2]],
            "top2_probs": [top1_prob, top2_prob],
            "motion_stats": motion_stats or {},
        }

    def _static_result(self, motion_stats):
        self.stable_label = self.config.static_display_label
        self.stable_prob = 1.0
        self.pred_history.clear()
        return {
            "raw_model_label": "skipped_static_gate",
            "raw_model_prob": 1.0,
            "stable_label": self.config.static_display_label,
            "stable_prob": 1.0,
            "is_static": True,
            "is_low_confidence": False,
            "ambiguous_slip_eccentricity": False,
            "top2_labels": [self.config.static_report_label, "skipped"],
            "top2_probs": [1.0, 0.0],
            "motion_stats": motion_stats,
        }

    def _is_ambiguous_slip_eccentricity(self, top1, top2, margin):
        pair = {LABEL_NAMES[top1], LABEL_NAMES[top2]}
        if pair != {"wheel_slip", "shaft_eccentricity"}:
            return False
        return margin < self.config.margin_threshold

    def _mean_prob_for_label(self, label):
        values = [prob for item_label, prob in self.pred_history if item_label == label]
        if not values:
            return 0.0
        return float(np.mean(values))

    def _check_window_shape(self, window):
        expected = (self.config.input_channels, self.config.window_size)
        if window.shape != expected:
            raise ValueError(f"Expected input window shape {expected}, got {window.shape}")

    def append_log_row(self, path, result):
        path = Path(path)
        row = {
            "raw_model_label": result["raw_model_label"],
            "raw_model_prob": result["raw_model_prob"],
            "stable_label": result["stable_label"],
            "stable_prob": result["stable_prob"],
            "is_static": result["is_static"],
            "is_low_confidence": result["is_low_confidence"],
            "ambiguous_slip_eccentricity": result["ambiguous_slip_eccentricity"],
            "top2_labels": "|".join(result["top2_labels"]),
            "top2_probs": "|".join(f"{v:.6f}" for v in result["top2_probs"]),
        }
        row.update(result.get("motion_stats", {}))
        fieldnames = list(row.keys())
        write_header = not path.exists()
        with path.open("a", newline="", encoding="utf-8-sig") as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames)
            if write_header:
                writer.writeheader()
            writer.writerow(row)


def save_default_config(path):
    path = Path(path)
    config = GuardConfig()
    path.write_text(json.dumps(asdict(config), ensure_ascii=False, indent=2), encoding="utf-8")


def demo_on_dataset(args):
    guard = SAGECNNRealtimeGuard.from_config_file(args.config) if args.config else SAGECNNRealtimeGuard()
    x_test = np.load(args.dataset_window)
    count = min(args.num_windows, x_test.shape[0])
    for index in range(count):
        result = guard.predict_window(x_test[index], already_scaled=True)
        print(index, json.dumps(result, ensure_ascii=False))


def parse_args():
    parser = argparse.ArgumentParser(description="Real-time deployment guard for SAGE-CNN.")
    parser.add_argument("--write_default_config", type=Path)
    parser.add_argument("--config", type=Path)
    parser.add_argument("--dataset_window", type=Path, default=Path("dataset_four_class_v1/X_test.npy"))
    parser.add_argument("--num_windows", type=int, default=5)
    return parser.parse_args()


def main():
    args = parse_args()
    if args.write_default_config:
        save_default_config(args.write_default_config)
        print(f"Saved default guard config to {args.write_default_config}")
        return
    demo_on_dataset(args)


if __name__ == "__main__":
    main()
