/*
 * DistanceSensorArrayROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef DISTANCESENSORARRAYROS_H_
#define DISTANCESENSORARRAYROS_H_

#include <memory>

#include "rec/robotino/api2/DistanceSensorArray.h"

#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/point_cloud.hpp>

class DistanceSensorArrayROS: public rec::robotino::api2::DistanceSensorArray
{
public:
	DistanceSensorArrayROS(std::shared_ptr<rclcpp::Node> node);
	~DistanceSensorArrayROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr distances_pub_;

	sensor_msgs::msg::PointCloud distances_msg_;

	builtin_interfaces::msg::Time stamp_;

	void distancesChangedEvent(const float* distances, unsigned int size);

};


#endif /* DISTANCESENSORARRAYROS_H_ */
