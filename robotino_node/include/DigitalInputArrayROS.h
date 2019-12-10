/*
 * DigitalInputArrayROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef DIGITALINPUTARRAYROS_H_
#define DIGITALINPUTARRAYROS_H_

#include <memory>

#include "rec/robotino/api2/DigitalInputArray.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/digital_readings.hpp"
#include "builtin_interfaces/msg/time.hpp"

class DigitalInputArrayROS: public rec::robotino::api2::DigitalInputArray
{
public:
	DigitalInputArrayROS(std::shared_ptr<rclcpp::Node> node);
	~DigitalInputArrayROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<robotino_msgs::msg::DigitalReadings>::SharedPtr digital_pub_;

	robotino_msgs::msg::DigitalReadings digital_msg_;

	builtin_interfaces::msg::Time stamp_;

	virtual void valuesChangedEvent(const int* values, unsigned int size);
};

#endif /* DIGITALINPUTARRAYROS_H_ */
