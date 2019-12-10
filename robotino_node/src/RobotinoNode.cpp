/*
 * RobotinoNode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include <cmath>
#include <chrono>

#include "RobotinoNode.h"

using namespace std::chrono_literals;

RobotinoNode::RobotinoNode() :
  	Node("robotino_node"),
    analog_input_array_(this->shared_from_this()),
    bumper_(this->shared_from_this()),
    compact_bha_(this->shared_from_this()),
    com_(this->shared_from_this()),
    digital_input_array_(this->shared_from_this()),
    digital_output_array_(this->shared_from_this()),
    distance_sensor_array_(this->shared_from_this()),
    electrical_gripper_(this->shared_from_this()),
    encoder_input_(this->shared_from_this()),
    grappler_(this->shared_from_this()),
    motor_array_(this->shared_from_this()),
    north_star_(this->shared_from_this()),
    omni_drive_(this->shared_from_this()),
    power_management_(this->shared_from_this())
{
    declare_parameter("hostname", "IP address of the robot");
    if(!get_parameter("hostname", hostname_))
    {
        hostname_ = "172.26.1.1";
    }

    //TODO (vcoelen) description des paramètres
    declare_parameter("max_linear_vel", "");
    if(!get_parameter("max_linear_vel", max_linear_vel_))
    {
        max_linear_vel_ = 0.2;
    }

    declare_parameter("min_linear_vel", "");
    if(!get_parameter("min_linear_vel", min_linear_vel_))
    {
        min_linear_vel_ = 0.05;
    }

    declare_parameter("max_angular_vel", "");
    if(!get_parameter("max_angular_vel", max_angular_vel_))
    {
        max_angular_vel_ = 1.0;
    }

    declare_parameter("min_angular_vel", "");
    if(!get_parameter("min_angular_vel", min_angular_vel_))
    {
        min_angular_vel_ = 0.1;
    }

    declare_parameter("downsample_kinect", "");
    if(!get_parameter("downsample_kinect", downsample_kinect_))
    {
        downsample_kinect_ = true;
    }

    declare_parameter("leaf_size_kinect", "");
    if(!get_parameter("leaf_size_kinect", leaf_size_kinect_))
    {
        leaf_size_kinect_ = 0.05;
    }

	distances_clearing_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud>("/distance_sensors_clearing", 1); //removed latching TODO (vcoelen) has to be fixed
	joint_states_pub_= this->create_publisher<sensor_msgs::msg::JointState>("/robotino_joint_states", 1); // removed latching=false TODO (vcoelen) has to be fixed

	com_.setName( "RobotinoNode" );

	initModules();
	initMsgs();

	timer_ = this->create_wall_timer( 33ms, std::bind(&RobotinoNode::timer_callback, this));
}

RobotinoNode::~RobotinoNode()
{


}

void RobotinoNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	analog_input_array_.setComId( com_.id() );
	bumper_.setComId( com_.id() );
	compact_bha_.setComId( com_.id() );
	digital_input_array_.setComId( com_.id() );
	digital_output_array_.setComId( com_.id() );
	distance_sensor_array_.setComId( com_.id() );
	electrical_gripper_.setComId( com_.id() );
	encoder_input_.setComId( com_.id() );
	grappler_.setComId( com_.id() );
	// kinect_.setComId( com_.id() );
	motor_array_.setComId( com_.id() );
	north_star_.setComId( com_.id() );
	omni_drive_.setComId( com_.id() );
	power_management_.setComId( com_.id() );

	omni_drive_.setMaxMin(max_linear_vel_, min_linear_vel_, max_angular_vel_, min_angular_vel_ );

	// kinect_.setDownsample( downsample_kinect_ );
	// kinect_.setLeafSize( leaf_size_kinect_ );

	com_.connectToServer( false );
}

void RobotinoNode::initMsgs()
{
	distances_clearing_msg_.header.frame_id = "base_link";
	distances_clearing_msg_.header.stamp = curr_time_;
	distances_clearing_msg_.points.resize( 720 );

	for( unsigned int i = 0; i < distances_clearing_msg_.points.size(); ++i )
	{
		distances_clearing_msg_.points[i].x = 5.0 * cos(  0.008727 ); // 0.008727 = 0.5 degrees in radians
		distances_clearing_msg_.points[i].y = 5.0 * sin(  0.008727 );
		distances_clearing_msg_.points[i].z = 0.05; // 5cm above ground
	}

	joint_state_msg_.name.resize(3);
	joint_state_msg_.position.resize(3, 0.0);
	joint_state_msg_.velocity.resize(3, 0.0);
	joint_state_msg_.name[0] = "wheel2_joint";
	joint_state_msg_.name[1] = "wheel0_joint";
	joint_state_msg_.name[2] = "wheel1_joint";

	motor_velocities_.resize(4);
	motor_positions_.resize(4);
}

void RobotinoNode::publishDistanceMsg()
{
//	curr_time_ = node_->now();
//	if( ( curr_time_ - clearing_time_ ).toSec() > 1 )
//	{
//		clearing_time_ = curr_time_;
//		distances_clearing_pub_->publish( distances_clearing_msg_ );
//	}
	distances_clearing_pub_->publish( distances_clearing_msg_ );
}

void RobotinoNode::publishJointStateMsg()
{
	motor_array_.getMotorReadings( motor_velocities_, motor_positions_ );

	joint_state_msg_.velocity[0] = ( ( motor_velocities_[2] / 16 ) * (2 * 3.142) / 60 );
	joint_state_msg_.velocity[1] = ( ( motor_velocities_[0] / 16 ) * (2 * 3.142) / 60 );
	joint_state_msg_.velocity[2] = ( ( motor_velocities_[1] / 16 ) * (2 * 3.142) / 60 );

	joint_state_msg_.position[0] = ( motor_positions_[2] / 16 ) * (2 * 3.142);
	joint_state_msg_.position[1] = ( motor_positions_[0] / 16 ) * (2 * 3.142);
	joint_state_msg_.position[2] = ( motor_positions_[1] / 16 ) * (2 * 3.142);

	joint_state_msg_.header.stamp = curr_time_;
	joint_states_pub_->publish( joint_state_msg_ );
}

void RobotinoNode::timer_callback()
{
	curr_time_ = now();

	analog_input_array_.setTimeStamp(curr_time_);
	compact_bha_.setTimeStamp(curr_time_);
	digital_input_array_.setTimeStamp(curr_time_);
	distance_sensor_array_.setTimeStamp(curr_time_);
	electrical_gripper_.setTimeStamp(curr_time_);
	encoder_input_.setTimeStamp(curr_time_);
	grappler_.setTimeStamp(curr_time_);
	// kinect_.setTimeStamp(curr_time_);
	motor_array_.setTimeStamp(curr_time_);
	north_star_.setTimeStamp(curr_time_);
	power_management_.setTimeStamp(curr_time_);

	publishDistanceMsg();
	publishJointStateMsg();
	com_.processEvents();
}
