cmake_minimum_required(VERSION 3.5)
project(robotino_msgs)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

find_package(rosidl_default_generators REQUIRED)

set(msg_files
	msg/AnalogReadings.msg
	msg/EncoderReadings.msg
	msg/MotorReadings.msg
	msg/SetBHAPressures.msg
	msg/BHAReadings.msg
	msg/GrapplerReadings.msg
	msg/NorthStarReadings.msg
	msg/SetGrapplerAxes.msg
	msg/DigitalReadings.msg
	msg/GripperState.msg
	msg/PowerReadings.msg
	msg/SetGrapplerAxis.msg
)

# Generate services in the 'srv' folder
set(srv_files
	srv/ResetOdometry.srv
	srv/SetEncoderPosition.srv
	srv/SetGripperState.srv
)

#Generate added messages and services with any dependencies listed here
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
DEPENDENCIES
  std_msgs
geometry_msgs)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
