/*
 * RobotinoNode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ROBOTINOODOMETRYNODE_H_
#define ROBOTINOODOMETRYNODE_H_

#include <memory>

#include "ComROS.h"
#include "OdometryROS.h"

#include "rclcpp/rclcpp.hpp"

class RobotinoOdometryNode : public rclcpp::Node
{
public:
	RobotinoOdometryNode();
	~RobotinoOdometryNode();

private:
	rclcpp::TimerBase::SharedPtr timer_;

	std::string hostname_;

	ComROS com_;
	OdometryROS odometry_;

	void initModules();
	void timer_callback();
};

#endif /* ROBOTINOODOMETRYNODE_H_ */
