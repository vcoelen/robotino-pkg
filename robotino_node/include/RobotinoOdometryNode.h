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

class RobotinoOdometryNode
{
public:
	RobotinoOdometryNode();
	~RobotinoOdometryNode();

	bool spin();

private:
	std::shared_ptr<rclcpp::Node> node_;

	std::string hostname_;

	ComROS com_;
	OdometryROS odometry_;

	void initModules();
};

#endif /* ROBOTINOODOMETRYNODE_H_ */
