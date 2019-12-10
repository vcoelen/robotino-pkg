/*
 * RobotinoNode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ROBOTINONODE_H_
#define ROBOTINONODE_H_

#include <memory>

#include "AnalogInputArrayROS.h"
#include "BumperROS.h"
#include "CompactBHAROS.h"
#include "ComROS.h"
#include "DigitalInputArrayROS.h"
#include "DigitalOutputArrayROS.h"
#include "DistanceSensorArrayROS.h"
#include "ElectricalGripperROS.h"
#include "EncoderInputROS.h"
#include "GrapplerROS.h"
// #include "KinectROS.h"
#include "MotorArrayROS.h"
#include "NorthStarROS.h"
#include "OmniDriveROS.h"
#include "PowerManagementROS.h"

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/point_cloud.hpp>
#include <sensor_msgs/msg/joint_state.hpp>


class RobotinoNode : public rclcpp::Node
{
public:
	RobotinoNode();
	~RobotinoNode();

private:
	//std::shared_ptr<rclcpp::Node> node_;
	rclcpp::TimerBase::SharedPtr timer_;

	std::string hostname_;
	double max_linear_vel_, min_linear_vel_, max_angular_vel_, min_angular_vel_;
	bool downsample_kinect_;
	double leaf_size_kinect_;

	std::vector<float> motor_velocities_;
	std::vector<int> motor_positions_;

	builtin_interfaces::msg::Time curr_time_, clearing_time_;

	rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr distances_clearing_pub_;
	rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_states_pub_;

	sensor_msgs::msg::PointCloud distances_clearing_msg_;
	sensor_msgs::msg::JointState joint_state_msg_;

	AnalogInputArrayROS analog_input_array_;
	BumperROS bumper_;
	CompactBHAROS compact_bha_;
	ComROS com_;
	DigitalInputArrayROS digital_input_array_;
	DigitalOutputArrayROS digital_output_array_;
	DistanceSensorArrayROS distance_sensor_array_;
	ElectricalGripperROS electrical_gripper_;
	EncoderInputROS encoder_input_;
	GrapplerROS grappler_;
	// KinectROS kinect_;
	MotorArrayROS motor_array_;
	NorthStarROS north_star_;
	OmniDriveROS omni_drive_;
	PowerManagementROS power_management_;

	void initModules();
	void initMsgs();
	void publishDistanceMsg();
	void publishJointStateMsg();

	void timer_callback();

};

#endif /* ROBOTINONODE_H_ */
