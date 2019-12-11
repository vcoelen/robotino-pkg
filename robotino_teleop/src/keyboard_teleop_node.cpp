/*
 * keyboard_teleop_node.cpp
 *
 *  Created on: 11.01.2012
 *      Author: indorewala@servicerobotics.eu
 */

#include "KeyboardTeleop.h"

#include <termios.h>
#include <signal.h>

#include <thread>

int kfd = 0;
struct termios cooked, raw;

#include "rclcpp/rclcpp.hpp"

void quit(int sig)
{
	tcsetattr(kfd, TCSANOW, &cooked);
	exit(0);
}

int main( int argc, char** argv )
{
	rclcpp::init(argc, argv);

	signal(SIGINT,quit);

	std::shared_ptr<KeyboardTeleop> kt = std::make_shared<KeyboardTeleop>(cooked, raw, kfd);

	std::thread kt_thread(std::bind(&KeyboardTeleop::spin, kt));
	rclcpp::spin(kt);

	kt_thread.join();
	rclcpp::shutdown();

	return 0;
}
