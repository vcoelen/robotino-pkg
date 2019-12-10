/*
 * ElectricalGripperROS.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "ElectricalGripperROS.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

ElectricalGripperROS::ElectricalGripperROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	gripper_pub_ = node_->create_publisher<robotino_msgs::msg::GripperState>("gripper_state", 1); //removed latching TODO (vcoelen) has to be fixed
	set_gripper_server_ = node_->create_service<robotino_msgs::srv::SetGripperState>("set_gripper_state",
			std::bind(&ElectricalGripperROS::setGripperStateService, this, _1, _2, _3));
}

ElectricalGripperROS::~ElectricalGripperROS()
{


}

void ElectricalGripperROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void ElectricalGripperROS::setGripperStateService(
	const std::shared_ptr<rmw_request_id_t> request_header,
	const std::shared_ptr<robotino_msgs::srv::SetGripperState::Request> req,
	const std::shared_ptr<robotino_msgs::srv::SetGripperState::Response> res)
{
	RCLCPP_INFO(node_->get_logger(), "request gripper state : %s", req->state ? "true" : "false");
	if( req->state )
		open();
	else
		close();

}

void ElectricalGripperROS::stateChangedEvent( int state )
{
	// Build the GripperState msg
	gripper_msg_.stamp = stamp_;
	if( state == ElectricalGripper::IsOpen )
		gripper_msg_.state = true;
	else
		gripper_msg_.state = false;

	// Publish the msg
	gripper_pub_->publish( gripper_msg_ );
}
