/*
 * OdometryROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ODOMETRYROS_H_
#define ODOMETRYROS_H_

#include <memory>

#include "rec/robotino/api2/Odometry.h"

#include "rclcpp/rclcpp.hpp"
#include <tf2_ros/transform_broadcaster.h>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include "robotino_msgs/srv/reset_odometry.hpp"

class OdometryROS: public rec::robotino::api2::Odometry
{
public:
	OdometryROS(std::shared_ptr<rclcpp::Node> node);
	~OdometryROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odometry_pub_;

	rclcpp::Service<robotino_msgs::srv::ResetOdometry>::SharedPtr reset_odometry_server_;

	nav_msgs::msg::Odometry odometry_msg_;
	geometry_msgs::msg::TransformStamped odometry_transform_;

	std::shared_ptr<tf2_ros::TransformBroadcaster> odometry_transform_broadcaster_;

	builtin_interfaces::msg::Time stamp_;


	void readingsEvent(double x, double y, double phi,
			float vx, float vy, float omega, unsigned int sequence );
	void resetOdometryService(
		const std::shared_ptr<rmw_request_id_t> request_header,
		const std::shared_ptr<robotino_msgs::srv::ResetOdometry::Request> req,
		const std::shared_ptr<robotino_msgs::srv::ResetOdometry::Response> res);
};

#endif /* ODOMETRYROS_H_ */
