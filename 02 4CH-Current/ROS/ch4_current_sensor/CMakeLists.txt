cmake_minimum_required(VERSION 3.0.2)
project(ch4_current_sensor)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  sensor_msgs
  diagnostic_msgs
  message_generation
)

add_message_files(
  FILES
  CurrentData.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
    rospy
    std_msgs
    sensor_msgs
    diagnostic_msgs
    message_runtime
)

catkin_install_python(PROGRAMS
  scripts/sensor_node.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)
