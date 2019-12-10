/*
 * OdometryROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "OdometryROS.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/transform_datatypes.h>
#include <geometry_msgs/msg/quaternion.hpp>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

OdometryROS::OdometryROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	odometry_pub_ = node_->create_publisher<nav_msgs::msg::Odometry>("odom", 1); //removed latching TODO (vcoelen) has to be fixed

	reset_odometry_server_ = node_->create_service<robotino_msgs::srv::ResetOdometry>("reset_odometry",
			std::bind(&OdometryROS::resetOdometryService, this, _1, _2, _3));

	std::make_shared<tf2_ros::TransformBroadcaster>(node_);
}

OdometryROS::~OdometryROS()
{


}

void OdometryROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}
void OdometryROS::readingsEvent(double x, double y, double phi,
		float vx, float vy, float omega, unsigned int sequence )
{
	geometry_msgs::msg::Quaternion phi_quat;
	tf2::Quaternion quat;
	quat.setRPY(0.0, 0.0, phi);
	phi_quat.x = quat.x();
	phi_quat.y = quat.y();
	phi_quat.z = quat.z();
	phi_quat.w = quat.w();

	// Construct messages
	odometry_msg_.header.frame_id = "odom";
	odometry_msg_.header.stamp = stamp_;
	odometry_msg_.child_frame_id = "base_link";
	odometry_msg_.pose.pose.position.x = x ;
	odometry_msg_.pose.pose.position.y = y ;
	odometry_msg_.pose.pose.position.z = 0.0;
	odometry_msg_.pose.pose.orientation = phi_quat;
	odometry_msg_.twist.twist.linear.x = vx;
	odometry_msg_.twist.twist.linear.y = vy;
	odometry_msg_.twist.twist.linear.z = 0.0;
	odometry_msg_.twist.twist.angular.x = 0.0;
	odometry_msg_.twist.twist.angular.y = 0.0;
	odometry_msg_.twist.twist.angular.z = omega;

	odometry_transform_.header.frame_id = "odom";
	odometry_transform_.header.stamp = odometry_msg_.header.stamp;
	odometry_transform_.child_frame_id = "base_link";
	odometry_transform_.transform.translation.x = x;
	odometry_transform_.transform.translation.y = y;
	odometry_transform_.transform.translation.z = 0.0;
	odometry_transform_.transform.rotation = phi_quat;

	odometry_transform_broadcaster_->sendTransform( odometry_transform_ );

	// Publish the msg
	odometry_pub_->publish( odometry_msg_ );
}

bool OdometryROS::resetOdometryService(
	const std::shared_ptr<rmw_request_id_t> request_header,
	const std::shared_ptr<robotino_msgs::srv::ResetOdometry::Request> req,
	const std::shared_ptr<robotino_msgs::srv::ResetOdometry::Response> res)
{
	(void)request_header;
	RCLCPP_INFO(node_->get_logger(), "Request reset Odometry");
	set( req->x, req->y, req->phi, true );
}
