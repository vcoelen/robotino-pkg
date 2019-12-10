/*
 * DigitalOutputArrayROS.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef DIGITALOUTPUTARRAYROS_H_
#define DIGITALOUTPUTARRAYROS_H_

#include <memory>

#include "rec/robotino/api2/DigitalOutputArray.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/digital_readings.hpp"

class DigitalOutputArrayROS: public rec::robotino::api2::DigitalOutputArray
{
public:
	DigitalOutputArrayROS(std::shared_ptr<rclcpp::Node> node);
	~DigitalOutputArrayROS();

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Subscription<robotino_msgs::msg::DigitalReadings>::SharedPtr digital_sub_;

	void setDigitalValuesCallback( const robotino_msgs::msg::DigitalReadings::SharedPtr msg);

};

#endif /* DIGITALOUTPUTARRAYROS_H_ */
