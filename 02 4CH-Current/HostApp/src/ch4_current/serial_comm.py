"""Serial communication module for 4CH-Current sensor.

This module handles serial port communication, including port scanning,
data transmission, and reception.
"""

import logging
import threading
from typing import Callable, Optional

import serial
import serial.tools.list_ports
from serial import Serial

from .protocol import CurrentData, ProtocolCommand, ProtocolParser

logger = logging.getLogger(__name__)


class SerialComm:
    """Serial communication handler for 4CH-Current sensor."""

    def __init__(self, baudrate: int = 115200, timeout: float = 1.0) -> None:
        """Initialize serial communication.

        Args:
            baudrate: Serial baudrate (default: 115200)
            timeout: Read timeout in seconds (default: 1.0)
        """
        self._baudrate = baudrate
        self._timeout = timeout
        self._serial: Optional[Serial] = None
        self._parser = ProtocolParser()
        self._running = False
        self._thread: Optional[threading.Thread] = None
        self._data_callback: Optional[Callable[[CurrentData], None]] = None

    @staticmethod
    def list_ports() -> list[str]:
        """List available serial ports.

        Returns:
            List of port names
        """
        ports = serial.tools.list_ports.comports()
        return [port.device for port in ports]

    def connect(self, port: str) -> bool:
        """Connect to serial port.

        Args:
            port: Serial port name (e.g., 'COM3', '/dev/ttyUSB0')

        Returns:
            True if connection successful, False otherwise
        """
        try:
            self._serial = Serial(
                port=port, baudrate=self._baudrate, timeout=self._timeout, write_timeout=1.0
            )
            logger.info(f"Connected to {port} at {self._baudrate} baud")
            return True
        except serial.SerialException as e:
            logger.error(f"Failed to connect to {port}: {e}")
            return False

    def disconnect(self) -> None:
        """Disconnect from serial port."""
        self.stop_reading()
        if self._serial and self._serial.is_open:
            self._serial.close()
            logger.info("Serial port closed")

    def is_connected(self) -> bool:
        """Check if serial port is connected.

        Returns:
            True if connected, False otherwise
        """
        return self._serial is not None and self._serial.is_open

    def send_command(self, cmd: ProtocolCommand, data: bytes = b"") -> bool:
        """Send a command to the device.

        Args:
            cmd: Protocol command
            data: Command payload (optional)

        Returns:
            True if sent successfully, False otherwise
        """
        if not self.is_connected():
            logger.error("Cannot send command: not connected")
            return False

        try:
            frame = self._parser.build_frame(cmd, data)
            assert self._serial is not None
            self._serial.write(frame)
            logger.debug(f"Sent command {cmd.name}: {frame.hex()}")
            return True
        except (serial.SerialException, ValueError) as e:
            logger.error(f"Failed to send command: {e}")
            return False

    def set_data_callback(self, callback: Callable[[CurrentData], None]) -> None:
        """Set callback function for received current data.

        Args:
            callback: Function to call when current data is received
        """
        self._data_callback = callback

    def start_reading(self) -> None:
        """Start background thread for reading serial data."""
        if self._running:
            logger.warning("Reading thread already running")
            return

        self._running = True
        self._thread = threading.Thread(target=self._read_loop, daemon=True)
        self._thread.start()
        logger.info("Started reading thread")

    def stop_reading(self) -> None:
        """Stop background reading thread."""
        if not self._running:
            return

        self._running = False
        if self._thread:
            self._thread.join(timeout=2.0)
            self._thread = None
        logger.info("Stopped reading thread")

    def _read_loop(self) -> None:
        """Background thread loop for reading serial data."""
        while self._running and self._serial:
            try:
                if self._serial.in_waiting > 0:
                    data = self._serial.read(self._serial.in_waiting)
                    self._process_data(data)
            except serial.SerialException as e:
                logger.error(f"Serial read error: {e}")
                break
            except Exception as e:
                logger.exception(f"Unexpected error in read loop: {e}")
                break

    def _process_data(self, data: bytes) -> None:
        """Process received data and invoke callbacks.

        Args:
            data: Raw bytes from serial port
        """
        result = self._parser.parse_frame(data)
        if result is None:
            return

        cmd, payload = result

        try:
            if cmd == ProtocolCommand.REPORT_CURRENT:
                current_data = self._parser.parse_current_data(payload)
                if self._data_callback:
                    self._data_callback(current_data)
            elif cmd == ProtocolCommand.QUERY_VERSION:
                version = self._parser.parse_version(payload)
                logger.info(f"Firmware version: {version.major}.{version.minor}.{version.patch}")
            elif cmd == ProtocolCommand.ACK:
                logger.info("Command acknowledged")
            elif cmd == ProtocolCommand.NACK:
                logger.warning("Command not acknowledged")
        except ValueError as e:
            logger.error(f"Failed to parse payload: {e}")
