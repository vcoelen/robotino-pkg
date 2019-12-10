/*
 * DigitalInputArrayROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "DigitalInputArrayROS.h"

DigitalInputArrayROS::DigitalInputArrayROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	digital_pub_ = node_->create_publisher<robotino_msgs::msg::DigitalReadings>("digital_readings", 1); //removed latching TODO (vcoelen) has to be fixed
}

DigitalInputArrayROS::~DigitalInputArrayROS()
{

}

void DigitalInputArrayROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void DigitalInputArrayROS::valuesChangedEvent(const int* values, unsigned int size)
{
	// Build the DigitalReadings msg
	digital_msg_.stamp = stamp_;
	digital_msg_.values.resize( size );

	if( size > 0 )
	{
		for (int idx=0; idx<size; ++idx)
		{
			digital_msg_.values[idx] = (bool)values[idx];
 		}

		// Publish the msg
		digital_pub_->publish( digital_msg_ );
	}

}
