/*
 * BumperROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "BumperROS.h"

BumperROS::BumperROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	// TODO (vcoelen) : In ROS1 this publisher was using latching that doesn't exist (yet? in Eloquent) in ROS2
	// So latching is removed, has to be fixed later
	// Instead there is a possibility to use QoS, see :
	// - https://github.com/ros2/ros2/issues/464
	// - http://docs.ros2.org/alpha8/rclcpp_cpp_client_library_overview.html#advanced-alternative-ways-to-create-publishers
	bumper_pub_ = node_->create_publisher<std_msgs::msg::Bool>("bumper", 1);
}

BumperROS::~BumperROS()
{
}

void BumperROS::bumperEvent(bool hasContact)
{
	bumper_msg_.data = hasContact;
	bumper_pub_->publish(bumper_msg_);
}
