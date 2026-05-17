#!/usr/bin/env python3
"""ROS node for 4-channel current sensor.

This node reads data from the 4CH-Current sensor via serial port
and publishes it as ROS messages.
"""

import struct
from enum import IntEnum
from typing import Optional

import rospy
import serial
from ch4_current_sensor.msg import CurrentData
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
from std_msgs.msg import Header


class ProtocolCommand(IntEnum):
    """Protocol command codes."""

    REPORT_CURRENT = 0x80
    QUERY_CURRENT = 0x01
    QUERY_RAW_ADC = 0x02


class SensorNode:
    """ROS node for 4-channel current sensor."""

    HEADER = bytes([0xAA, 0x55])
    TAIL = bytes([0x0D, 0x0A])

    def __init__(self) -> None:
        """Initialize the sensor node."""
        rospy.init_node("ch4_current_sensor", anonymous=False)

        # Parameters
        self._port = rospy.get_param("~port", "/dev/ttyUSB0")
        self._baudrate = rospy.get_param("~baudrate", 115200)
        self._publish_rate = rospy.get_param("~publish_rate", 10.0)

        # Publishers
        self._data_pub = rospy.Publisher("current_data", CurrentData, queue_size=10)
        self._diag_pub = rospy.Publisher("/diagnostics", DiagnosticArray, queue_size=1)

        # Serial port
        self._serial: Optional[serial.Serial] = None
        self._buffer = bytearray()

        # Statistics
        self._frame_count = 0
        self._error_count = 0

        rospy.loginfo(f"Initializing sensor node on {self._port} at {self._baudrate} baud")

    def connect(self) -> bool:
        """Connect to serial port.

        Returns:
            True if connection successful
        """
        try:
            self._serial = serial.Serial(
                port=self._port, baudrate=self._baudrate, timeout=1.0
            )
            rospy.loginfo(f"Connected to {self._port}")
            return True
        except serial.SerialException as e:
            rospy.logerr(f"Failed to connect to {self._port}: {e}")
            return False

    def disconnect(self) -> None:
        """Disconnect from serial port."""
        if self._serial and self._serial.is_open:
            self._serial.close()
            rospy.loginfo("Disconnected from serial port")

    @staticmethod
    def calc_checksum(cmd: int, data: bytes) -> int:
        """Calculate XOR checksum.

        Args:
            cmd: Command byte
            data: Data bytes

        Returns:
            XOR checksum
        """
        checksum = cmd ^ len(data)
        for byte in data:
            checksum ^= byte
        return checksum

    def parse_frame(self, data: bytes) -> Optional[tuple[int, bytes]]:
        """Parse incoming data and extract valid frames.

        Args:
            data: Incoming bytes

        Returns:
            Tuple of (command, payload) if valid frame found
        """
        self._buffer.extend(data)

        while len(self._buffer) >= 7:
            header_pos = self._buffer.find(self.HEADER)
            if header_pos == -1:
                self._buffer.clear()
                return None

            if header_pos > 0:
                self._buffer = self._buffer[header_pos:]

            if len(self._buffer) < 7:
                return None

            cmd = self._buffer[2]
            data_len = self._buffer[3]
            frame_len = 2 + 1 + 1 + data_len + 1 + 2

            if len(self._buffer) < frame_len:
                return None

            frame_data = bytes(self._buffer[4 : 4 + data_len])
            received_checksum = self._buffer[4 + data_len]
            tail = bytes(self._buffer[4 + data_len + 1 : 4 + data_len + 3])

            self._buffer = self._buffer[frame_len:]

            if tail != self.TAIL:
                self._error_count += 1
                continue

            calculated_checksum = self.calc_checksum(cmd, frame_data)
            if received_checksum != calculated_checksum:
                self._error_count += 1
                continue

            return (cmd, frame_data)

        return None

    def parse_current_data(self, data: bytes) -> Optional[CurrentData]:
        """Parse current data payload.

        Args:
            data: 16-byte current data payload

        Returns:
            Parsed current data message
        """
        if len(data) != 16:
            return None

        values = struct.unpack("<ffff", data)

        msg = CurrentData()
        msg.header = Header()
        msg.header.stamp = rospy.Time.now()
        msg.header.frame_id = "ch4_current_sensor"
        msg.ch0_current = values[0]
        msg.ch1_current = values[1]
        msg.ch2_current = values[2]
        msg.ch3_current = values[3]

        return msg

    def read_and_publish(self) -> None:
        """Read data from sensor and publish."""
        if not self._serial or not self._serial.is_open:
            return

        try:
            if self._serial.in_waiting > 0:
                data = self._serial.read(self._serial.in_waiting)
                result = self.parse_frame(data)

                if result:
                    cmd, payload = result

                    if cmd == ProtocolCommand.REPORT_CURRENT:
                        current_msg = self.parse_current_data(payload)
                        if current_msg:
                            self._data_pub.publish(current_msg)
                            self._frame_count += 1

        except serial.SerialException as e:
            rospy.logerr(f"Serial read error: {e}")
            self._error_count += 1

    def publish_diagnostics(self) -> None:
        """Publish diagnostic information."""
        diag_array = DiagnosticArray()
        diag_array.header.stamp = rospy.Time.now()

        status = DiagnosticStatus()
        status.name = "4CH Current Sensor"
        status.hardware_id = self._port

        if self._serial and self._serial.is_open:
            status.level = DiagnosticStatus.OK
            status.message = "Connected and receiving data"
        else:
            status.level = DiagnosticStatus.ERROR
            status.message = "Not connected"

        status.values = [
            KeyValue(key="Frames Received", value=str(self._frame_count)),
            KeyValue(key="Errors", value=str(self._error_count)),
            KeyValue(key="Port", value=self._port),
            KeyValue(key="Baudrate", value=str(self._baudrate)),
        ]

        diag_array.status.append(status)
        self._diag_pub.publish(diag_array)

    def run(self) -> None:
        """Main run loop."""
        if not self.connect():
            return

        rate = rospy.Rate(self._publish_rate)
        diag_rate = rospy.Rate(1.0)  # 1 Hz for diagnostics

        rospy.loginfo("Sensor node running")

        while not rospy.is_shutdown():
            self.read_and_publish()

            if diag_rate.remaining() <= rospy.Duration(0):
                self.publish_diagnostics()
                diag_rate.sleep()

            rate.sleep()

        self.disconnect()


def main() -> None:
    """Main entry point."""
    try:
        node = SensorNode()
        node.run()
    except rospy.ROSInterruptException:
        pass


if __name__ == "__main__":
    main()
