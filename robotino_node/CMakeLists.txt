cmake_minimum_required(VERSION 3.5)
project(robotino_node)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(image_transport REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(robotino_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL 1.2 REQUIRED)

# Attention, modif à faire après TOUS les find_package()
set(
    CMAKE_MODULE_PATH
    /opt/robotino/cmake
)
find_package(RobotinoAPI2 REQUIRED)


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(include
    ${REC_ROBOTINO_API2_INCLUDE_DIRS}
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
    src/LaserRangeFinderROS.cpp
    src/MotorArrayROS.cpp
    src/NorthStarROS.cpp
    src/OdometryROS.cpp
    src/OmniDriveROS.cpp
    src/PowerManagementROS.cpp
    src/RobotinoNode.cpp
)

ament_target_dependencies(robotino_node
    rclcpp
    geometry_msgs
    std_msgs
    nav_msgs
    cv_bridge
    tf2
    tf2_ros
    image_transport
    sensor_msgs
    robotino_msgs)

target_link_libraries(
 	robotino_node
  	${REC_ROBOTINO_API2_LIBRARY}
	${PCL_LIBRARIES}
)

add_executable(
    robotino_odometry_node
    src/robotino_odometry_node.cpp
    src/ComROS.cpp
    src/OdometryROS.cpp
    src/RobotinoOdometryNode.cpp
)

ament_target_dependencies(robotino_odometry_node
    rclcpp
    geometry_msgs
    std_msgs
    nav_msgs
    cv_bridge
    tf2
    tf2_ros
    image_transport
    sensor_msgs
    robotino_msgs)

target_link_libraries(
    robotino_odometry_node
    ${REC_ROBOTINO_API2_LIBRARY}
)
#
# add_executable(
#   robotino_laserrangefinder_node
#   src/robotino_laserrangefinder_node.cpp
#   src/ComROS.cpp
#   src/LaserRangeFinderROS.cpp
#   src/RobotinoLaserRangeFinderNode.cpp
# )
#
# add_dependencies(robotino_laserrangefinder_node ${catkin_EXPORTED_TARGETS})
#
# target_link_libraries(
#   robotino_laserrangefinder_node
#   ${REC_ROBOTINO_API2_LIBRARY}
#   ${catkin_LIBRARIES}
# )
#
# add_executable(
#   robotino_camera_node
#   src/robotino_camera_node.cpp
#   src/ComROS.cpp
#   src/CameraROS.cpp
#   src/RobotinoCameraNode.cpp
# )
#
# add_dependencies(robotino_camera_node ${catkin_EXPORTED_TARGETS})
#
# target_link_libraries(
#   robotino_camera_node
#   ${REC_ROBOTINO_API2_LIBRARY}
#   ${catkin_LIBRARIES}
# )
#
#
# # Mark executables and/or libraries for installation
# install(TARGETS robotino_node robotino_odometry_node robotino_laserrangefinder_node robotino_camera_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )


ament_package()
