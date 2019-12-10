/*
 * DigitalOutputArrayROS.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include <cstring>

#include "DigitalOutputArrayROS.h"

using std::placeholders::_1;

DigitalOutputArrayROS::DigitalOutputArrayROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	digital_sub_ = node_->create_subscription<robotino_msgs::msg::DigitalReadings>("set_digital_values", 1,
			std::bind(&DigitalOutputArrayROS::setDigitalValuesCallback, this, _1));
}

DigitalOutputArrayROS::~DigitalOutputArrayROS()
{

}

void DigitalOutputArrayROS::setDigitalValuesCallback( const robotino_msgs::msg::DigitalReadings::SharedPtr msg)
{
	int numValues = msg->values.size();
	if( numValues > 0 )
	{
		bool values[numValues];

		//TODO (vcoelen)
		//std::memcpy( values, msg->values.data(), numValues * sizeof(bool) );
		//setValues( values, numValues );
	}
}
