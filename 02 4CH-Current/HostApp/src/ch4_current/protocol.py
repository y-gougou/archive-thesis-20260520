"""4-Channel Current Sensor Protocol Parser.

This module implements the binary protocol parser for communication
with the 4CH-Current STM32 firmware.
"""

import struct
from dataclasses import dataclass
from enum import IntEnum
from typing import Optional


class ProtocolCommand(IntEnum):
    """Protocol command codes."""

    # Query commands (0x01-0x1F)
    QUERY_CURRENT = 0x01
    QUERY_RAW_ADC = 0x02
    QUERY_CALIBRATION = 0x03
    QUERY_VERSION = 0x04

    # Set commands (0x20-0x3F)
    SET_CALIBRATION = 0x20
    SET_SAMPLE_RATE = 0x21
    SET_FILTER = 0x22

    # Report commands (0x80-0x9F)
    REPORT_CURRENT = 0x80
    REPORT_ERROR = 0x81

    # System commands (0xF0-0xFF)
    ACK = 0xF0
    NACK = 0xF1
    RESET = 0xFF


@dataclass
class CurrentData:
    """Current measurement data from all 4 channels."""

    ch0: float
    ch1: float
    ch2: float
    ch3: float


@dataclass
class RawAdcData:
    """Raw ADC values from all 4 channels."""

    ch0: int
    ch1: int
    ch2: int
    ch3: int


@dataclass
class VersionInfo:
    """Firmware version information."""

    major: int
    minor: int
    patch: int


class ProtocolParser:
    """Binary protocol parser for 4CH-Current sensor.

    Frame format:
        | Header(2B) | CMD(1B) | LEN(1B) | DATA(NB) | CRC(1B) | Tail(2B) |
        | AA 55      | CMD     | LEN     | DATA     | XOR     | 0D 0A    |
    """

    HEADER = bytes([0xAA, 0x55])
    TAIL = bytes([0x0D, 0x0A])
    MAX_DATA_LEN = 32

    def __init__(self) -> None:
        """Initialize the protocol parser."""
        self._buffer = bytearray()

    @staticmethod
    def calc_checksum(cmd: int, data: bytes) -> int:
        """Calculate XOR checksum.

        Args:
            cmd: Command byte
            data: Data bytes

        Returns:
            XOR checksum value
        """
        checksum = cmd ^ len(data)
        for byte in data:
            checksum ^= byte
        return checksum

    def build_frame(self, cmd: ProtocolCommand, data: bytes = b"") -> bytes:
        """Build a complete protocol frame.

        Args:
            cmd: Protocol command
            data: Data payload (optional)

        Returns:
            Complete frame bytes

        Raises:
            ValueError: If data length exceeds maximum
        """
        if len(data) > self.MAX_DATA_LEN:
            raise ValueError(f"Data length {len(data)} exceeds maximum {self.MAX_DATA_LEN}")

        frame = bytearray()
        frame.extend(self.HEADER)
        frame.append(cmd)
        frame.append(len(data))
        frame.extend(data)
        frame.append(self.calc_checksum(cmd, data))
        frame.extend(self.TAIL)

        return bytes(frame)

    def parse_frame(self, data: bytes) -> Optional[tuple[ProtocolCommand,bytes]]:
        """Parse incoming data and extract valid frames.

        Args:
            data: Incoming bytes

        Returns:
            Tuple of (command, payload) if valid frame found, None otherwise
        """
        self._buffer.extend(data)

        # Search for frame header
        while len(self._buffer) >= 7:  # Minimum frame size
            # Find header
            header_pos = self._buffer.find(self.HEADER)
            if header_pos == -1:
                self._buffer.clear()
                return None

            # Remove bytes before header
            if header_pos > 0:
                self._buffer = self._buffer[header_pos:]

            # Check if we have enough data
            if len(self._buffer) < 7:
                return None

            cmd = self._buffer[2]
            data_len = self._buffer[3]

            frame_len = 2 + 1 + 1 + data_len + 1 + 2  # Full frame length

            if len(self._buffer) < frame_len:
                return None  # Wait for more data

            # Extract frame
            frame_data = bytes(self._buffer[4 : 4 + data_len])
            received_checksum = self._buffer[4 + data_len]
            tail = bytes(self._buffer[4 + data_len + 1 : 4 + data_len + 3])

            # Remove processed frame
            self._buffer = self._buffer[frame_len:]

            # Validate tail
            if tail != self.TAIL:
                continue

            # Validate checksum
            calculated_checksum = self.calc_checksum(cmd, frame_data)
            if received_checksum != calculated_checksum:
                continue

            return (ProtocolCommand(cmd), frame_data)

        return None

    @staticmethod
    def parse_current_data(data: bytes) -> CurrentData:
        """Parse current data payload.

        Args:
            data: 16-byte current data payload

        Returns:
            Parsed current data

        Raises:
            ValueError: If data length is incorrect
        """
        if len(data) != 16:
            raise ValueError(f"Current data must be 16 bytes, got {len(data)}")

        values = struct.unpack("<ffff", data)
        return CurrentData(ch0=values[0], ch1=values[1], ch2=values[2], ch3=values[3])

    @staticmethod
    def parse_raw_adc(data: bytes) -> RawAdcData:
        """Parse raw ADC data payload.

        Args:
            data: 8-byte raw ADC data payload

        Returns:
            Parsed raw ADC data

        Raises:
            ValueError: If data length is incorrect
        """
        if len(data) != 8:
            raise ValueError(f"Raw ADC data must be 8 bytes, got {len(data)}")

        values = struct.unpack("<HHHH", data)
        return RawAdcData(ch0=values[0], ch1=values[1], ch2=values[2], ch3=values[3])

    @staticmethod
    def parse_version(data: bytes) -> VersionInfo:
        """Parse version information payload.

        Args:
            data: 4-byte version data payload

        Returns:
            Parsed version information

        Raises:
            ValueError: If data length is incorrect
        """
        if len(data) != 4:
            raise ValueError(f"Version data must be 4 bytes, got {len(data)}")

        return VersionInfo(major=data[0], minor=data[1], patch=data[2])
