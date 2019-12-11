/*
 * KeyboardTeleop.h
 *
 *  Created on: 11.01.2012
 *      Author: indorewala@servicerobotics.eu
 */

/*
 * Functionality borrowed from turtlebot_teleop
 */

#ifndef KEYBOARDTELEOP_H_
#define KEYBOARDTELEOP_H_

#include <termios.h>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/time.hpp"
#include "rclcpp/clock.hpp"
#include <geometry_msgs/msg/twist.hpp>


#define KEYCODE_Z 0x7A
#define KEYCODE_Q 0x71
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64

#define KEYCODE_A 0x61
#define KEYCODE_E 0x65

#define KEYCODE_W 0x77

#define KEYCODE_SPACE 0x20

class KeyboardTeleop : public rclcpp::Node
{
public:
	KeyboardTeleop( struct termios &cooked, struct termios &raw, int &kfd );
	~KeyboardTeleop();

private:
	rclcpp::Clock wall_clock_;
	rclcpp::TimerBase::SharedPtr timer_watchdog_;

	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
	rclcpp::Time first_publish_, last_publish_;

	geometry_msgs::msg::Twist cmd_vel_msg_;

	double scale_linear_, scale_angular_;
	struct termios cooked_, raw_;
	int kfd_;

	std::mutex publish_mutex_;

	void readParams();
	void publish( double vel_x, double vel_y, double vel_omega );

	void watchdog();
public:
	void spin();
};


#endif /* KEYBOARDTELEOP_H_ */
