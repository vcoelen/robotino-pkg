cmake_minimum_required(VERSION 2.8.3)
project(robotino_node)

set(
  CMAKE_MODULE_PATH
  /usr/local/robotino/api2/cmake
)

find_package(OpenCV REQUIRED)

find_package(PCL 1.2 REQUIRED)

find_package(catkin REQUIRED COMPONENTS 
geometry_msgs std_msgs message_generation roscpp roslib OpenCV cv_bridge tf image_transport robotino_msgs)

find_package(RobotinoAPI2)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(include
  ${catkin_INCLUDE_DIRS}
)


add_executable(
  robotino_node
  src/robotino_node.cpp
  src/AnalogInputArrayROS.cpp
  src/BumperROS.cpp
  src/CameraROS.cpp
  src/CompactBHAROS.cpp
  src/ComROS.cpp
  src/DigitalInputArrayROS.cpp
  src/DigitalOutputArrayROS.cpp
  src/DistanceSensorArrayROS.cpp
  src/ElectricalGripperROS.cpp
  src/EncoderInputROS.cpp
  src/GrapplerROS.cpp
  #src/KinectROS.cpp
  src/LaserRangeFinderROS.cpp
  src/MotorArrayROS.cpp
  src/NorthStarROS.cpp
  src/OdometryROS.cpp
  src/OmniDriveROS.cpp
  src/PowerManagementROS.cpp
  src/RobotinoNode.cpp
)

add_dependencies(robotino_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
 	robotino_node
  	${REC_ROBOTINO_API2_LIBRARY}
	${catkin_LIBRARIES}
	${PCL_LIBRARIES}
)

add_executable(
  robotino_odometry_node
  src/robotino_odometry_node.cpp
  src/ComROS.cpp
  src/OdometryROS.cpp
  src/RobotinoOdometryNode.cpp
)


add_dependencies(robotino_odometry_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  robotino_odometry_node
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

add_executable(
  robotino_laserrangefinder_node
  src/robotino_laserrangefinder_node.cpp
  src/ComROS.cpp
  src/LaserRangeFinderROS.cpp
  src/RobotinoLaserRangeFinderNode.cpp
)

add_dependencies(robotino_laserrangefinder_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  robotino_laserrangefinder_node
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

add_executable(
  robotino_camera_node
  src/robotino_camera_node.cpp
  src/ComROS.cpp
  src/CameraROS.cpp
  src/RobotinoCameraNode.cpp
)

add_dependencies(robotino_camera_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  robotino_camera_node
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

add_executable(
  robotino_mapping_node
  src/robotino_mapping_node.cpp
  src/MappingROS.cpp
  src/RobotinoMappingNode.cpp
  src/InitialPoseROS.cpp
  src/NavGoalROS.cpp
  src/ComROS.cpp
)

add_dependencies(robotino_mapping_node ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  robotino_mapping_node
  ${REC_ROBOTINO_API2_LIBRARY}
  ${catkin_LIBRARIES}
)

# Mark executables and/or libraries for installation
install(TARGETS robotino_node robotino_odometry_node robotino_laserrangefinder_node robotino_mapping_node robotino_camera_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)