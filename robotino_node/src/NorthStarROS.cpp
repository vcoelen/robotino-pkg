/*
 * NorthStarROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "NorthStarROS.h"

#include <tf2/transform_datatypes.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/msg/quaternion.h>

NorthStarROS::NorthStarROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	north_star_pub_ = node_->create_publisher<robotino_msgs::msg::NorthStarReadings>("north_star", 1); //removed latching TODO (vcoelen) has to be fixed
}

NorthStarROS::~NorthStarROS()
{

}

void NorthStarROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void NorthStarROS::readingsEvent( const rec::robotino::api2::NorthStarReadings& readings )
{
	//geometry_msgs::msg::Quaternion quat = tf2_ros::createQuaternionMsgFromYaw(readings.posTheta);
	geometry_msgs::msg::Quaternion quat_msg;
	tf2::Quaternion quat;
    quat.setRPY(0.0, 0.0, readings.posTheta);
    quat_msg.x = quat.x();
    quat_msg.y = quat.y();
    quat_msg.z = quat.z();
    quat_msg.w = quat.w();


	// Build the NorthStarReadings msg
	north_star_msg_.stamp 				= stamp_;
	north_star_msg_.seq 				= readings.sequenceNumber;
	north_star_msg_.room_id 			= readings.roomId;
	north_star_msg_.num_spots_visible 	= readings.numSpotsVisible;
	north_star_msg_.pose.position.x 	= readings.posX;
	north_star_msg_.pose.position.y 	= readings.posY;
	north_star_msg_.pose.position.z 	= 0.0;
	north_star_msg_.pose.orientation	= quat_msg;

	// Publish the message
	north_star_pub_->publish( north_star_msg_ );
}
