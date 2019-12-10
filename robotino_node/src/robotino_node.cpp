/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


//#include <sensor_msgs/msg/fill_image.h>

#include "RobotinoNode.h"

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<RobotinoNode>());
	rclcpp::shutdown();
	return 0;
}
