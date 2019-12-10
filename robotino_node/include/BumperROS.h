/*
 * BumperROS.h
 *
 *  Created on: 06.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef BUMPERROS_H_
#define BUMPERROS_H_

#include <memory>

#include "rec/robotino/api2/Bumper.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class BumperROS: public rec::robotino::api2::Bumper
{
public:
	BumperROS(std::shared_ptr<rclcpp::Node> node);
	~BumperROS();

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr bumper_pub_;

	std_msgs::msg::Bool bumper_msg_;

	void bumperEvent(bool hasContact);
};

#endif /* BUMPERROS_H_ */
