cmake_minimum_required(VERSION 2.8.3)
project(robotino_msgs)

find_package(catkin REQUIRED COMPONENTS geometry_msgs std_msgs message_generation roscpp roslib)

add_message_files(
	FILES
	AnalogReadings.msg   
	EncoderReadings.msg   
	MotorReadings.msg      
	SetBHAPressures.msg
	BHAReadings.msg      
	GrapplerReadings.msg  
	NorthStarReadings.msg  
	SetGrapplerAxes.msg
	DigitalReadings.msg  
	GripperState.msg      
	PowerReadings.msg      
	SetGrapplerAxis.msg
)

# Generate services in the 'srv' folder
add_service_files(
	FILES
	ResetOdometry.srv  
	SetEncoderPosition.srv  
	SetGripperState.srv
)

#Generate added messages and services with any dependencies listed here
generate_messages(
 	DEPENDENCIES
  	std_msgs
	geometry_msgs 
)


#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
