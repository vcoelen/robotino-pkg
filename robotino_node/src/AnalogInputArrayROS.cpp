/*
 * AnalogInputArrayROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "AnalogInputArrayROS.h"

AnalogInputArrayROS::AnalogInputArrayROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	analog_pub_ = node_->create_publisher<robotino_msgs::msg::AnalogReadings>("analog_readings", 1); //removed latching TODO (vcoelen) has to be fixed
}

AnalogInputArrayROS::~AnalogInputArrayROS()
{
}

void AnalogInputArrayROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void AnalogInputArrayROS::valuesChangedEvent( const float* values, unsigned int size )
{
	// Build the AnalogReadings msg
	analog_msg_.stamp = stamp_;
	analog_msg_.values.resize(size);

	if( size > 0 )
	{
		memcpy( analog_msg_.values.data(), values, size * sizeof( float ) );

		// Publish the msg
		analog_pub_->publish(analog_msg_);
	}
}
