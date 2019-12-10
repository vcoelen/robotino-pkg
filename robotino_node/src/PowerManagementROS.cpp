/*
 * PowerManagementROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "PowerManagementROS.h"

PowerManagementROS::PowerManagementROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	power_pub_ = node_->create_publisher<robotino_msgs::msg::PowerReadings>("power_readings", 1); //removed latching TODO (vcoelen) has to be fixed
}

PowerManagementROS::~PowerManagementROS()
{

}

void PowerManagementROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void PowerManagementROS::readingsEvent(float current, float voltage)
{
	// Build the PowerReadings msg
	power_msg_.stamp = node_->now();
	power_msg_.current = current;
	power_msg_.voltage = voltage;

	// Publish the msg
	power_pub_->publish( power_msg_ );
}
