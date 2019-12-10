/*
 * AnalogInputArrayROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ANALOGINPUTARRAYROS_H_
#define ANALOGINPUTARRAYROS_H_

#include <memory>

#include "rec/robotino/api2/AnalogInputArray.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/analog_readings.hpp"

class AnalogInputArrayROS: public rec::robotino::api2::AnalogInputArray
{
public:
	AnalogInputArrayROS(std::shared_ptr<rclcpp::Node> node);
	~AnalogInputArrayROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<robotino_msgs::msg::AnalogReadings>::SharedPtr analog_pub_;

	robotino_msgs::msg::AnalogReadings analog_msg_;

	builtin_interfaces::msg::Time stamp_;

	void valuesChangedEvent( const float* values, unsigned int size );

};


#endif /* ANALOGINPUTARRAYROS_H_ */
