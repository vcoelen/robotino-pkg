/*
 * LaserRangeFinderROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef LASERRANGEFINDERROS_H_
#define LASERRANGEFINDERROS_H_

#include <memory>

#include "rec/robotino/api2/LaserRangeFinder.h"
#include "rec/robotino/api2/LaserRangeFinderReadings.h"

#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>

class LaserRangeFinderROS: public rec::robotino::api2::LaserRangeFinder
{
public:
	LaserRangeFinderROS(std::shared_ptr<rclcpp::Node> node);
	~LaserRangeFinderROS();

	void setNumber( int number );
	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr laser_scan_pub_;

	sensor_msgs::msg::LaserScan laser_scan_msg_;

	builtin_interfaces::msg::Time stamp_;

	void scanEvent(const rec::robotino::api2::LaserRangeFinderReadings &scan);
};

#endif /* LASERRANGEFINDERROS_H_ */
