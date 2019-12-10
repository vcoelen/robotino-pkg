/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RobotinoOdometryNode.h"

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<RobotinoOdometryNode>());
	rclcpp::shutdown();
	return 0;
}
