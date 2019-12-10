/*
 * CompactBHAROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef COMPACTBHAROS_H_
#define COMPACTBHAROS_H_

#include <memory>

#include "rec/robotino/api2/CompactBHA.h"

#include "rclcpp/rclcpp.hpp"
#include "builtin_interfaces/msg/time.hpp"
#include "robotino_msgs/msg/bha_readings.hpp"
#include "robotino_msgs/msg/set_bha_pressures.hpp"

class CompactBHAROS : public rec::robotino::api2::CompactBHA
{
public:
	CompactBHAROS(std::shared_ptr<rclcpp::Node> node);
	~CompactBHAROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Subscription<robotino_msgs::msg::SetBHAPressures>::SharedPtr bha_sub_;

	rclcpp::Publisher<robotino_msgs::msg::BHAReadings>::SharedPtr bha_pub_;

	robotino_msgs::msg::BHAReadings bha_msg_;

	builtin_interfaces::msg::Time stamp_;

	void pressuresChangedEvent( const float* pressures, unsigned int size );
	void cablepullChangedEvent( const float* cablepull, unsigned int size );

	void setBHAPressuresCallback( const robotino_msgs::msg::SetBHAPressures::SharedPtr msg);
};

#endif /* COMPACTBHAROS_H_ */
