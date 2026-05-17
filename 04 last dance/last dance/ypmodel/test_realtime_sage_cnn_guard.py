import numpy as np

from realtime_sage_cnn_guard import GuardConfig, SAGECNNRealtimeGuard


def make_guard():
    config = GuardConfig(
        static_required_windows=5,
        vote_window_size=5,
        vote_required_count=3,
        low_confidence_threshold=0.70,
        margin_threshold=0.15,
    )
    return SAGECNNRealtimeGuard(config=config, device="cpu")


def assert_static_gate():
    guard = make_guard()
    static_window = np.zeros((15, 50), dtype=np.float32)
    result = None
    for _ in range(5):
        result = guard.predict_window(static_window, already_scaled=True)
    assert result["is_static"] is True
    assert result["stable_label"] == "normal_static"
    assert result["raw_model_label"] == "skipped_static_gate"


def assert_non_static_model_path():
    guard = make_guard()
    moving_window = np.zeros((15, 50), dtype=np.float32)
    moving_window[0, :] = 0.5
    moving_window[3:6, :] = 0.5
    result = guard.predict_window(moving_window, already_scaled=True)
    assert result["is_static"] is False
    assert result["raw_model_label"] in {
        "normal",
        "drive_abnormal",
        "wheel_slip",
        "shaft_eccentricity",
    }


def assert_temporal_vote_holds_normal():
    guard = make_guard()
    seq = [
        [0.90, 0.04, 0.03, 0.03],
        [0.92, 0.03, 0.03, 0.02],
        [0.10, 0.80, 0.05, 0.05],
        [0.88, 0.04, 0.04, 0.04],
        [0.91, 0.03, 0.03, 0.03],
    ]
    result = None
    for probs in seq:
        result = guard.update_from_probabilities(np.asarray(probs))
    assert result["stable_label"] == "normal"


def assert_ambiguous_slip_eccentricity_hold():
    guard = make_guard()
    guard.update_from_probabilities(np.asarray([0.05, 0.05, 0.85, 0.05]))
    guard.update_from_probabilities(np.asarray([0.05, 0.05, 0.86, 0.04]))
    stable = guard.update_from_probabilities(np.asarray([0.05, 0.05, 0.87, 0.03]))
    assert stable["stable_label"] == "wheel_slip"
    result = guard.update_from_probabilities(np.asarray([0.05, 0.05, 0.43, 0.47]))
    assert result["ambiguous_slip_eccentricity"] is True
    assert result["stable_label"] == "wheel_slip"


def assert_fault_switch_after_consensus():
    guard = make_guard()
    seq = [
        [0.05, 0.05, 0.85, 0.05],
        [0.05, 0.05, 0.86, 0.04],
        [0.05, 0.05, 0.87, 0.03],
    ]
    result = None
    for probs in seq:
        result = guard.update_from_probabilities(np.asarray(probs))
    assert result["stable_label"] == "wheel_slip"


def main():
    assert_static_gate()
    assert_non_static_model_path()
    assert_temporal_vote_holds_normal()
    assert_ambiguous_slip_eccentricity_hold()
    assert_fault_switch_after_consensus()
    print("realtime_sage_cnn_guard tests passed")


if __name__ == "__main__":
    main()
