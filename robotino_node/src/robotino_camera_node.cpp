/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RobotinoCameraNode.h"

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "robotino_camera_node");
	RobotinoCameraNode rn;
	rn.spin();
	return 0;
}
