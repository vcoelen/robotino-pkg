/*
 * MotorArrayROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef MOTORARRAYROS_H_
#define MOTORARRAYROS_H_

#include <memory>

#include "rec/robotino/api2/MotorArray.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/motor_readings.hpp"

class MotorArrayROS : public rec::robotino::api2::MotorArray
{
public:
	MotorArrayROS(std::shared_ptr<rclcpp::Node> node);
	~MotorArrayROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);
	void getMotorReadings(std::vector<float> &velocities, std::vector<int> &positions );

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<robotino_msgs::msg::MotorReadings>::SharedPtr motor_pub_;

	robotino_msgs::msg::MotorReadings motor_msg_;

	builtin_interfaces::msg::Time stamp_;

	void velocitiesChangedEvent( const float* velocities, unsigned int size );
	void positionsChangedEvent( const float* positions, unsigned int size );
	void currentsChangedEvent( const float* currents, unsigned int size );
};
#endif /* MOTORARRAYROS_H_ */
