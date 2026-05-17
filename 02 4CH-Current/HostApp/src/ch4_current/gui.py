"""PySide6 GUI application for 4CH-Current sensor.

This module implements the main window and user interface components.
"""

import csv
import logging
from datetime import datetime
from pathlib import Path
from typing import Optional

import numpy as np
import pyqtgraph as pg
from PySide6.QtCore import QTimer, Signal, Slot
from PySide6.QtWidgets import (
    QComboBox,
    QGroupBox,
    QHBoxLayout,
    QLabel,
    QMainWindow,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

from .protocol import CurrentData, ProtocolCommand
from .serial_comm import SerialComm

logger = logging.getLogger(__name__)


class MainWindow(QMainWindow):
    """Main application window for 4CH-Current sensor."""

    # Signal emitted when new current data is received
    data_received = Signal(CurrentData)

    def __init__(self) -> None:
        """Initialize the main window."""
        super().__init__()
        self.setWindowTitle("4CH-Current Sensor Host Application")
        self.resize(1200, 800)

        # Serial communication
        self._serial = SerialComm()
        self._serial.set_data_callback(self._on_data_received)

        # Data recording
        self._recording = False
        self._csv_file: Optional[Path] = None
        self._csv_writer: Optional[csv.writer] = None

        # Plot data buffers
        self._max_points = 500
        self._time_data = np.zeros(self._max_points)
        self._current_data = [np.zeros(self._max_points) for _ in range(4)]
        self._data_index = 0

        # Setup UI
        self._setup_ui()

        # Connect signals
        self.data_received.connect(self._update_display)

        # Auto-refresh timer
        self._refresh_timer = QTimer()
        self._refresh_timer.timeout.connect(self._refresh_plot)
        self._refresh_timer.start(50)  # 20 Hz refresh rate

    def _setup_ui(self) -> None:
        """Setup user interface components."""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        main_layout = QHBoxLayout(central_widget)

        # Left panel: Controls
        control_panel = self._create_control_panel()
        main_layout.addWidget(control_panel, stretch=0)

        # Right panel: Plots and data
        plot_panel = self._create_plot_panel()
        main_layout.addWidget(plot_panel, stretch=1)

    def _create_control_panel(self) -> QWidget:
        """Create the control panel widget.

        Returns:
            Control panel widget
        """
        panel = QWidget()
        panel.setMaximumWidth(300)
        layout = QVBoxLayout(panel)

        # Connection group
        conn_group = QGroupBox("Connection")
        conn_layout = QVBoxLayout(conn_group)

        self._port_combo = QComboBox()
        conn_layout.addWidget(QLabel("Serial Port:"))
        conn_layout.addWidget(self._port_combo)

        refresh_ports_btn = QPushButton("Refresh Ports")
        refresh_ports_btn.clicked.connect(self._refresh_ports)
        conn_layout.addWidget(refresh_ports_btn)

        self._connect_btn = QPushButton("Connect")
        self._connect_btn.clicked.connect(self._toggle_connection)
        conn_layout.addWidget(self._connect_btn)

        layout.addWidget(conn_group)

        # Data recording group
        record_group = QGroupBox("Data Recording")
        record_layout = QVBoxLayout(record_group)

        self._record_btn = QPushButton("Start Recording")
        self._record_btn.clicked.connect(self._toggle_recording)
        self._record_btn.setEnabled(False)
        record_layout.addWidget(self._record_btn)

        layout.addWidget(record_group)

        # Commands group
        cmd_group = QGroupBox("Commands")
        cmd_layout = QVBoxLayout(cmd_group)

        query_version_btn = QPushButton("Query Version")
        query_version_btn.clicked.connect(self._query_version)
        cmd_layout.addWidget(query_version_btn)

        reset_device_btn = QPushButton("Reset Device")
        reset_device_btn.clicked.connect(self._reset_device)
        cmd_layout.addWidget(reset_device_btn)

        layout.addWidget(cmd_group)

        layout.addStretch()

        # Initial port scan
        self._refresh_ports()

        return panel

    def _create_plot_panel(self) -> QWidget:
        """Create the plot panel widget.

        Returns:
            Plot panel widget
        """
        panel = QWidget()
        layout = QVBoxLayout(panel)

        # Current values display
        values_group = QGroupBox("Current Values")
        values_layout = QHBoxLayout(values_group)

        self._value_labels = []
        channel_names = ["CH0 (M1)", "CH1 (M2)", "CH2 (M3)", "CH3 (M4)"]
        channel_colors = ["#FF6B6B", "#4ECDC4", "#45B7D1", "#FFA07A"]

        for i, (name, color) in enumerate(zip(channel_names, channel_colors)):
            ch_layout = QVBoxLayout()
            ch_layout.addWidget(QLabel(name))

            value_label = QLabel("0.000 A")
            value_label.setStyleSheet(
                f"font-size: 20px; font-weight: bold; color: {color}; "
                f"border: 2px solid {color}; padding: 5px; border-radius: 5px;"
            )
            ch_layout.addWidget(value_label)
            self._value_labels.append(value_label)

            values_layout.addLayout(ch_layout)

        layout.addWidget(values_group)

        # Plot widget
        self._plot_widget = pg.PlotWidget(title="Current vs Time")
        self._plot_widget.setBackground("w")
        self._plot_widget.setLabel("left", "Current (A)")
        self._plot_widget.setLabel("bottom", "Time (s)")
        self._plot_widget.addLegend()
        self._plot_widget.showGrid(x=True, y=True, alpha=0.3)

        # Create plot curves
        self._plot_curves = []
        for i, (name, color) in enumerate(zip(channel_names, channel_colors)):
            pen = pg.mkPen(color=color, width=2)
            curve = self._plot_widget.plot(
                self._time_data, self._current_data[i], name=name, pen=pen
            )
            self._plot_curves.append(curve)

        layout.addWidget(self._plot_widget)

        return panel

    @Slot()
    def _refresh_ports(self) -> None:
        """Refresh available serial ports."""
        ports = SerialComm.list_ports()
        self._port_combo.clear()
        self._port_combo.addItems(ports)
        logger.info(f"Found {len(ports)} serial ports")

    @Slot()
    def _toggle_connection(self) -> None:
        """Toggle serial connection."""
        if self._serial.is_connected():
            self._serial.disconnect()
            self._connect_btn.setText("Connect")
            self._record_btn.setEnabled(False)
            logger.info("Disconnected")
        else:
            port = self._port_combo.currentText()
            if self._serial.connect(port):
                self._serial.start_reading()
                self._connect_btn.setText("Disconnect")
                self._record_btn.setEnabled(True)
                logger.info(f"Connected to {port}")
            else:
                logger.error(f"Failed to connect to {port}")

    @Slot()
    def _toggle_recording(self) -> None:
        """Toggle data recording to CSV."""
        if self._recording:
            self._stop_recording()
        else:
            self._start_recording()

    def _start_recording(self) -> None:
        """Start recording data to CSV file."""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        self._csv_file = Path(f"current_data_{timestamp}.csv")

        try:
            file_handle = self._csv_file.open("w", newline="")
            self._csv_writer = csv.writer(file_handle)
            self._csv_writer.writerow(["Timestamp", "CH0 (A)", "CH1 (A)", "CH2 (A)", "CH3 (A)"])

            self._recording = True
            self._record_btn.setText("Stop Recording")
            logger.info(f"Started recording to {self._csv_file}")
        except OSError as e:
            logger.error(f"Failed to create CSV file: {e}")

    def _stop_recording(self) -> None:
        """Stop recording data."""
        self._recording = False
        self._record_btn.setText("Start Recording")

        if self._csv_file:
            logger.info(f"Stopped recording. File: {self._csv_file}")
            self._csv_file = None
            self._csv_writer = None

    @Slot()
    def _query_version(self) -> None:
        """Query firmware version from device."""
        self._serial.send_command(ProtocolCommand.QUERY_VERSION)

    @Slot()
    def _reset_device(self) -> None:
        """Send reset command to device."""
        self._serial.send_command(ProtocolCommand.RESET)

    def _on_data_received(self, data: CurrentData) -> None:
        """Callback for received current data.

        Args:
            data: Received current data
        """
        # Emit signal to update UI in main thread
        self.data_received.emit(data)

    @Slot(CurrentData)
    def _update_display(self, data: CurrentData) -> None:
        """Update display with new data.

        Args:
            data: Current data to display
        """
        # Update value labels
        values = [data.ch0, data.ch1, data.ch2, data.ch3]
        for label, value in zip(self._value_labels, values):
            label.setText(f"{value:.3f} A")

        # Update plot data
        idx = self._data_index % self._max_points
        self._time_data[idx] = self._data_index * 0.1  # Assuming 10 Hz update rate
        for i, value in enumerate(values):
            self._current_data[i][idx] = value

        self._data_index += 1

        # Record to CSV if enabled
        if self._recording and self._csv_writer:
            timestamp = datetime.now().isoformat()
            self._csv_writer.writerow([timestamp, *values])

    @Slot()
    def _refresh_plot(self) -> None:
        """Refresh plot display."""
        if self._data_index < self._max_points:
            # Show only received data
            for i, curve in enumerate(self._plot_curves):
                curve.setData(
                    self._time_data[: self._data_index], self._current_data[i][: self._data_index]
                )
        else:
            # Scrolling window
            for i, curve in enumerate(self._plot_curves):
                curve.setData(self._time_data, self._current_data[i])

    def closeEvent(self, event) -> None:  # type: ignore[no-untyped-def]
        """Handle window close event.

        Args:
            event: Close event
        """
        self._refresh_timer.stop()
        if self._recording:
            self._stop_recording()
        self._serial.disconnect()
        event.accept()
