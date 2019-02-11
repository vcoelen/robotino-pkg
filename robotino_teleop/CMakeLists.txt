cmake_minimum_required(VERSION 2.8.3)
project(robotino_teleop)

find_package(catkin REQUIRED COMPONENTS roscpp roslib robotino_node)

# Attention, modif à faire après TOUS les find_package()
set(
  CMAKE_MODULE_PATH
  /opt/robotino/cmake
)
find_package(RobotinoAPI2 REQUIRED)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${REC_ROBOTINO_API2_INCLUDE_DIRS}
)

add_executable(
	joystick_teleop_node 
	src/joystick_teleop_node.cpp
	src/JoystickTeleop.cpp)

add_dependencies(joystick_teleop_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  joystick_teleop_node 
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

add_executable(
	keyboard_teleop_node 
	src/keyboard_teleop_node.cpp
	src/KeyboardTeleop.cpp)

add_dependencies(keyboard_teleop_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  keyboard_teleop_node
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

# Mark executables and/or libraries for installation
install(TARGETS joystick_teleop_node keyboard_teleop_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)