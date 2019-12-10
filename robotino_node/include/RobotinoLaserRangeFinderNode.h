/*
 * RobotinoNode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ROBOTINOLaserRangeFinderNODE_H_
#define ROBOTINOLaserRangeFinderNODE_H_

#include <memory>

#include "ComROS.h"
#include "LaserRangeFinderROS.h"

#include "rclcpp/rclcpp.hpp"

class RobotinoLaserRangeFinderNode
{
public:
	RobotinoLaserRangeFinderNode();
	~RobotinoLaserRangeFinderNode();

	bool spin();

private:
	std::shared_ptr<rclcpp::Node> node_;

	std::string hostname_;
	int laserRangeFinderNumber_;

	ComROS com_;
	LaserRangeFinderROS laser_range_finder_;

	void initModules();
};

#endif /* ROBOTINOLaserRangeFinderNODE_H_ */
