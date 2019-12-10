/*
 * CompactBHAROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "CompactBHAROS.h"

using std::placeholders::_1;

CompactBHAROS::CompactBHAROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	bha_pub_ = node_->create_publisher<robotino_msgs::msg::BHAReadings>("bha_readings", 1); //removed latching TODO (vcoelen) has to be fixed
	bha_sub_ = node_->create_subscription<robotino_msgs::msg::SetBHAPressures>("set_bha_pressures", 1, std::bind(&CompactBHAROS::setBHAPressuresCallback, this, _1));
}

CompactBHAROS::~CompactBHAROS()
{


}

void CompactBHAROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void CompactBHAROS::pressuresChangedEvent( const float* pressures, unsigned int size )
{
	// Build the BHAReadings msg
	bha_msg_.pressures.resize( size, 0.0 );

	if( pressures != NULL )
	{
		memcpy( bha_msg_.pressures.data(), pressures, size * sizeof(float) );
	}
}

void CompactBHAROS::cablepullChangedEvent( const float* cablepull, unsigned int size )
{
	// Build the BHAReadings msg
	bha_msg_.cablepull.resize( size, 0.0 );
	if( cablepull != NULL )
	{
		memcpy( bha_msg_.cablepull.data(), cablepull, size * sizeof(float) );
	}

	// Publish the msg
	bha_pub_->publish( bha_msg_ );
}

void CompactBHAROS::setBHAPressuresCallback(const robotino_msgs::msg::SetBHAPressures::SharedPtr msg)
{
	float pressures[8];

	if( msg->pressures.size() == 8 )
	{
		for(int i = 0; i < 8; ++i)
		{
			pressures[i] = msg->pressures[i];
		}

		setPressures( pressures );
	}
}
