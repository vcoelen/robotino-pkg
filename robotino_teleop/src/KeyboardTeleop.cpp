/*
 * KeyboardTeleop.cpp
 *
 *  Created on: 11.01.2012
 *      Author: indorewala@servicerobotics.eu
 */

#include <chrono>
#include <mutex>
#include <unistd.h>

#include "rclcpp/duration.hpp"

#include "KeyboardTeleop.h"

using namespace std::chrono_literals;

KeyboardTeleop::KeyboardTeleop( struct termios &cooked, struct termios &raw, int &kfd ):
	Node("keyboard_teleop_node"),
	wall_clock_(RCL_STEADY_TIME),
	cooked_( cooked ),
	raw_( raw ),
	kfd_ ( kfd )
{
	cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 1); //TODO (vcoelen) removed latching add QoS
	readParams();

	first_publish_ = wall_clock_.now();
	last_publish_ = wall_clock_.now();

	timer_watchdog_ = this->create_wall_timer(100ms, std::bind(&KeyboardTeleop::watchdog, this));

}

KeyboardTeleop::~KeyboardTeleop()
{
}

void KeyboardTeleop::readParams()
{
	declare_parameter("scale_linear", 1.0);
    get_parameter_or("scale_linear", scale_linear_, 1.0);

	declare_parameter("scale_angular", 1.0);
    get_parameter_or("scale_angular", scale_angular_, 1.0);
}

void KeyboardTeleop::publish( double vel_x, double vel_y, double vel_omega )
{
	cmd_vel_msg_.linear.x 	= scale_linear_ * vel_x;
	cmd_vel_msg_.linear.y  	= scale_linear_ * vel_y;
	cmd_vel_msg_.angular.z 	= scale_angular_ * vel_omega;

	cmd_vel_pub_->publish( cmd_vel_msg_ );
}

void KeyboardTeleop::spin()
{
	char c;
	double vel_x, vel_y, vel_omega;

	// Get the console in raw mode
	tcgetattr( kfd_, &cooked_ );
	memcpy( &raw_, &cooked_, sizeof(struct termios) );
	raw_.c_lflag &=~ ( ICANON | ECHO );

	// Setting a new line, then end of file
	raw_.c_cc[VEOL] = 1;
	raw_.c_cc[VEOF] = 2;
	tcsetattr( kfd_, TCSANOW, &raw_ );

	puts("Reading from keyboard");
	puts("---------------------------");
	puts("Use 'ZQSD' for translation");
	puts("Use 'AE' for rotation");

	puts("Press 'Space' to STOP");

	while(rclcpp::ok())
	{
		vel_x = 0.0;
		vel_y = 0.0;
		vel_omega = 0.0;

		// get the next event from the keyboard
		if(read( kfd_, &c, 1 ) < 0)
		{
			perror("read():");
			exit(-1);
		}

		switch( c )
		{
		// Walking
		case KEYCODE_Z:
			vel_x = 0.05;
			break;
		case KEYCODE_S:
			vel_x = -0.05;
			break;
		case KEYCODE_Q:
			vel_y = 0.05;
			break;
		case KEYCODE_D:
			vel_y = -0.05;
			break;
		case KEYCODE_A:
			vel_omega = 0.5;
			break;
		case KEYCODE_E:
			vel_omega = -0.5;
			break;

		case KEYCODE_SPACE:
			vel_x = vel_y = vel_omega = 0.0;
			break;

		default:
			break;
		}

		std::scoped_lock lock(publish_mutex_);
		if (wall_clock_.now() > last_publish_ + rclcpp::Duration(1000s))
		{
			first_publish_ = wall_clock_.now();
		}
		last_publish_ = wall_clock_.now();
		publish( vel_x, vel_y, vel_omega );
	}
	return;
}

void KeyboardTeleop::watchdog()
{
	std::scoped_lock lock( publish_mutex_ );
	if ((wall_clock_.now() > last_publish_ + rclcpp::Duration(150ms)) &&
			(wall_clock_.now() > first_publish_ + rclcpp::Duration(500ms)))
		publish(0.0, 0.0, 0.0);
}
