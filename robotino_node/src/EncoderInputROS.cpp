/*
 * EncoderInputROS.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "EncoderInputROS.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

EncoderInputROS::EncoderInputROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	encoder_pub_ = node_->create_publisher<robotino_msgs::msg::EncoderReadings>("encoder_readings", 1); //removed latching TODO (vcoelen) has to be fixed
	encoder_position_server_ = node_->create_service<robotino_msgs::srv::SetEncoderPosition>("set_encoder_position",
			std::bind(&EncoderInputROS::setEncoderPositionService, this, _1, _2, _3));
}

EncoderInputROS::~EncoderInputROS()
{


}

void EncoderInputROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void EncoderInputROS::readingsChangedEvent( int velocity, int position, float current )
{
	// Build the EncoderReadings msg
	encoder_msg_.stamp = stamp_;
	encoder_msg_.velocity = velocity;
	encoder_msg_.position = position;
	encoder_msg_.current = current;

	// Publish the msg
	encoder_pub_->publish( encoder_msg_ );
}

void EncoderInputROS::setEncoderPositionService(
	const std::shared_ptr<rmw_request_id_t> request_header,
	const std::shared_ptr<robotino_msgs::srv::SetEncoderPosition::Request> req,
	const std::shared_ptr<robotino_msgs::srv::SetEncoderPosition::Response> res)
{
	(void)request_header;
	RCLCPP_INFO(node_->get_logger(), "Request set encoder position and velocity");
	setPosition( req->position ,req->velocity );
}
