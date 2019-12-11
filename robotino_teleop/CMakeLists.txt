cmake_minimum_required(VERSION 3.5)
project(robotino_teleop)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  # c++17 because I wanted to remove dependency to boost
  # std::scoped_lock is not available before c++17
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(robotino_node REQUIRED)

# Attention, modif à faire après TOUS les find_package()
set(
    CMAKE_MODULE_PATH
    /opt/robotino/cmake
)
find_package(RobotinoAPI2 REQUIRED)


include_directories(include
    ${REC_ROBOTINO_API2_INCLUDE_DIRS}
)

add_executable(
    joystick_teleop_node
    src/joystick_teleop_node.cpp
    src/JoystickTeleop.cpp
)

ament_target_dependencies(joystick_teleop_node
    rclcpp
    geometry_msgs
    sensor_msgs
    robotino_node
)

target_link_libraries(
    joystick_teleop_node
    ${REC_ROBOTINO_API2_LIBRARY}
)

add_executable(
	keyboard_teleop_node
	src/keyboard_teleop_node.cpp
	src/KeyboardTeleop.cpp
)

ament_target_dependencies(keyboard_teleop_node
    rclcpp
    geometry_msgs
    sensor_msgs
    robotino_node
)

target_link_libraries(
    keyboard_teleop_node
    ${REC_ROBOTINO_API2_LIBRARY}
)

install(TARGETS
    joystick_teleop_node
    keyboard_teleop_node
    DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
