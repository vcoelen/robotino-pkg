/*
 * ElectricalGripperROS.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ELECTRICALGRIPPERROS_H_
#define ELECTRICALGRIPPERROS_H_

#include <memory>

#include "rec/robotino/api2/ElectricalGripper.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/gripper_state.hpp"
#include "robotino_msgs/srv/set_gripper_state.hpp"


class ElectricalGripperROS : public rec::robotino::api2::ElectricalGripper
{
public:
	ElectricalGripperROS(std::shared_ptr<rclcpp::Node> node);
	~ElectricalGripperROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<robotino_msgs::msg::GripperState>::SharedPtr gripper_pub_;

	rclcpp::Service<robotino_msgs::srv::SetGripperState>::SharedPtr set_gripper_server_;

	robotino_msgs::msg::GripperState gripper_msg_;

	builtin_interfaces::msg::Time stamp_;

	void setGripperStateService(
		const std::shared_ptr<rmw_request_id_t> request_header,
		const std::shared_ptr<robotino_msgs::srv::SetGripperState::Request> req,
		const std::shared_ptr<robotino_msgs::srv::SetGripperState::Response> res);

	void stateChangedEvent( int state );

};

#endif /* ELECTRICALGRIPPERROS_H_ */
