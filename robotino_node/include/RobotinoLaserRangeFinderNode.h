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

class RobotinoLaserRangeFinderNode : public rclcpp::Node
{
public:
	RobotinoLaserRangeFinderNode();
	~RobotinoLaserRangeFinderNode();

private:
	rclcpp::TimerBase::SharedPtr timer_;

	std::string hostname_;
	int laserRangeFinderNumber_;

	ComROS com_;
	LaserRangeFinderROS laser_range_finder_;

	void initModules();
	void timer_callback();
};

#endif /* ROBOTINOLaserRangeFinderNODE_H_ */
