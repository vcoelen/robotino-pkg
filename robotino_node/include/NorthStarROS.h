/*
 * NorthStarROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef NORTHSTARROS_H_
#define NORTHSTARROS_H_

#include <memory>

#include "rec/robotino/api2/NorthStar.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/north_star_readings.hpp"

class NorthStarROS : public rec::robotino::api2::NorthStar
{
public:
	NorthStarROS(std::shared_ptr<rclcpp::Node> node);
	~NorthStarROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<robotino_msgs::msg::NorthStarReadings>::SharedPtr north_star_pub_;

	robotino_msgs::msg::NorthStarReadings north_star_msg_;

	builtin_interfaces::msg::Time stamp_;

	void readingsEvent( const rec::robotino::api2::NorthStarReadings& readings );
};

#endif /* NORTHSTARROS_H_ */
