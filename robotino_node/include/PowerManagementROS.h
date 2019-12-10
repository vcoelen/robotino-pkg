/*
 * PowerManagementROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef POWERMANAGEMENTROS_H_
#define POWERMANAGEMENTROS_H_

#include <memory>

#include "rec/robotino/api2/PowerManagement.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/power_readings.hpp"

class PowerManagementROS: public rec::robotino::api2::PowerManagement
{
public:
	PowerManagementROS(std::shared_ptr<rclcpp::Node> node);
	~PowerManagementROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;
	rclcpp::Publisher<robotino_msgs::msg::PowerReadings>::SharedPtr power_pub_;

	robotino_msgs::msg::PowerReadings power_msg_;

	builtin_interfaces::msg::Time stamp_;

	void readingsEvent(float current, float voltage);
};
#endif /* POWERMANAGEMENTROS_H_ */
