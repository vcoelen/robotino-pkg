/*
 * OmniDriveROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include <cmath>

#include "OmniDriveROS.h"

using std::placeholders::_1;

OmniDriveROS::OmniDriveROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	cmd_vel_sub_ = node_->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", 1, std::bind(&OmniDriveROS::cmdVelCallback, this, _1));
}

OmniDriveROS::~OmniDriveROS()
{

}

void OmniDriveROS::cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
	double linear_x = msg->linear.x;
	double linear_y = msg->linear.y;
	double angular = msg->angular.z;

	if ( std::abs( linear_x ) > max_linear_vel_ )
	{
		if( linear_x > 0.0 )
			linear_x = max_linear_vel_;
		else
			linear_x = -max_linear_vel_;
	}
	else if( std::abs( linear_x ) <  min_linear_vel_ && std::abs( linear_x ) > 0.0 )
	{
		if( linear_x > 0.0 )
			linear_x = min_linear_vel_;
		else
			linear_x = -min_linear_vel_;
	}

	if ( std::abs( linear_y ) > max_linear_vel_ )
	{
		if( linear_y > 0.0 )
			linear_y = max_linear_vel_;
		else
			linear_y = -max_linear_vel_;
	}
	else if( std::abs( linear_y ) <  min_linear_vel_ && std::abs( linear_y ) > 0.0 )
	{
		if( linear_y > 0.0 )
			linear_y = min_linear_vel_;
		else
			linear_y = -min_linear_vel_;
	}

	if ( std::abs( angular ) > max_angular_vel_ )
	{
		if( angular > 0.0 )
			angular = max_angular_vel_;
		else
			angular = -max_angular_vel_;
	}
	else if( std::abs( angular ) <  min_angular_vel_ && std::abs( angular ) > 0.0 )
	{
		if( angular > 0.0 )
			angular = min_angular_vel_;
		else
			angular = -min_angular_vel_;
	}

	setVelocity( linear_x, linear_y, angular);
}

void OmniDriveROS::setMaxMin( double max_linear_vel, double min_linear_vel,
		double max_angular_vel, double min_angular_vel )
{
	max_linear_vel_ = max_linear_vel;
	min_linear_vel_ = min_linear_vel;
	max_angular_vel_ = max_angular_vel;
	min_angular_vel_ = min_angular_vel;
}
