/*
 * RobotinoNode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef RobotinoCameraNode_H
#define RobotinoCameraNode_H

#include <memory>

#include "ComROS.h"
#include "CameraROS.h"

#include "rclcpp/rclcpp.hpp"

class RobotinoCameraNode : public rclcpp::Node
{
public:
	RobotinoCameraNode();
	~RobotinoCameraNode();

private:
	rclcpp::TimerBase::SharedPtr timer_;

	std::string hostname_;
	int cameraNumber_;

	ComROS com_;
	CameraROS camera_;

	void initModules();
	void timer_callback();
};

#endif /* RobotinoCameraNode_H */
