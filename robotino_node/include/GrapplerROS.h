/*
 * GrapplerROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef GRAPPLERROS_H_
#define GRAPPLERROS_H_

#include <memory>

#include "rec/robotino/api2/Grappler.h"
#include "rec/robotino/api2/GrapplerReadings.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/grappler_readings.hpp"
#include "robotino_msgs/msg/set_grappler_axes.hpp"
#include "robotino_msgs/msg/set_grappler_axis.hpp"

class GrapplerROS : public rec::robotino::api2::Grappler
{
public:
	GrapplerROS(std::shared_ptr<rclcpp::Node> node);
	~GrapplerROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Subscription<robotino_msgs::msg::SetGrapplerAxes>::SharedPtr grappler_axes_sub_;
	rclcpp::Subscription<robotino_msgs::msg::SetGrapplerAxis>::SharedPtr grappler_axis_sub_;

	rclcpp::Publisher<robotino_msgs::msg::GrapplerReadings>::SharedPtr grappler_readings_pub_;
	rclcpp::Publisher<robotino_msgs::msg::GrapplerReadings>::SharedPtr grappler_store_pub_;

	robotino_msgs::msg::GrapplerReadings grappler_readings_msg_;
	robotino_msgs::msg::GrapplerReadings grappler_store_msg_;

	builtin_interfaces::msg::Time stamp_;

	void readingsEvent( const rec::robotino::api2::GrapplerReadings& readings );
	void storePositionsEvent( const rec::robotino::api2::GrapplerReadings& readings );
	void setGrapplerAxes( const robotino_msgs::msg::SetGrapplerAxes::SharedPtr msg);
	void setGrapplerAxis( const robotino_msgs::msg::SetGrapplerAxis::SharedPtr msg);
};


#endif /* GRAPPLERROS_H_ */
