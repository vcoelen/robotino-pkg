/*
 * JoystickTeleop.cpp
 *
 *  Created on: 16.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include <chrono>
#include <memory>

#include "JoystickTeleop.h"

using namespace std::chrono_literals;
using std::placeholders::_1;

JoystickTeleop::JoystickTeleop() :
	Node("joystick_teleop_node")
{
	cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 1); //TODO (vcoelen) removed latching add QoS
	joy_sub_ = create_subscription<sensor_msgs::msg::Joy>("/joy", 1, std::bind(&JoystickTeleop::joyCallback, this, _1));

	readParams();

	timer_ = this->create_wall_timer( 200ms, std::bind(&JoystickTeleop::timer_callback, this));
}

JoystickTeleop::~JoystickTeleop()
{
}

void JoystickTeleop::readParams()
{

	declare_parameter("axis_linear_x", 1);
    if(!get_parameter("axis_linear_x", axis_linear_x_))
    {
 		axis_linear_x_ = 1;
    }

	declare_parameter("axis_linear_y", 0);
    if(!get_parameter("axis_linear_y", axis_linear_y_))
    {
 		axis_linear_y_ = 0;
    }

	declare_parameter("axis_angular", 2);
    if(!get_parameter("axis_angular", axis_angular_))
     {
 		axis_angular_ = 2;
    }

	declare_parameter("scale_linear", 0.1);
    if(!get_parameter("scale_linear", scale_linear_))
    {
 		scale_linear_ = 0.1;
    }

	declare_parameter("scale_angular", 0.2);
    if(!get_parameter("scale_angular", scale_angular_))
    {
 		scale_angular_ = 0.2;
    }

}

void JoystickTeleop::joyCallback( const sensor_msgs::msg::Joy::SharedPtr msg)
{
	if( msg->axes.size() < 3)
	{
		RCLCPP_ERROR(get_logger(), "Too few joystick axes: %d (expected more than 3)", msg->axes.size() );
		return;
	}

	cmd_vel_msg_.linear.x = msg->axes[axis_linear_x_] * scale_linear_;
	cmd_vel_msg_.linear.y = msg->axes[axis_linear_y_] * scale_linear_;
	cmd_vel_msg_.angular.z = msg->axes[axis_angular_] * scale_angular_;
}

void JoystickTeleop::timer_callback()
{
	cmd_vel_pub_->publish( cmd_vel_msg_ );
}
