cmake_minimum_required(VERSION 2.8.3)
project(robotino_safety)

find_package(catkin REQUIRED COMPONENTS roscpp roslib laser_geometry tf robotino_node)
find_package(RobotinoAPI2)

find_package(Eigen REQUIRED)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(${EIGEN_INCLUDE_DIRS})

add_definitions(${EIGEN_DEFINITIONS})

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${laser_geometry_INCLUDE_DIRS}
)

add_executable(
  robotino_safety_node 
  src/RobotinoSafety.cpp
  src/robotino_safety_node.cpp)

add_dependencies(robotino_safety_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  robotino_safety_node 
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

# Mark executables and/or libraries for installation
install(TARGETS robotino_safety_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)