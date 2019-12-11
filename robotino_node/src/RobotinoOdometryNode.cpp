/*
 * RobotinoNode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include <chrono>

#include "RobotinoOdometryNode.h"

using namespace std::chrono_literals;

RobotinoOdometryNode::RobotinoOdometryNode() :
 	Node("robotino_odometry_node"),
	com_(create_sub_node("")),
	odometry_(create_sub_node(""))
{
	declare_parameter("hostname", "192.168.10.2");
    if(!get_parameter("hostname", hostname_))
    {
        hostname_ = "192.168.10.2";
    }
	com_.setName( "Odometry" );

	initModules();

	timer_ = this->create_wall_timer( 33ms, std::bind(&RobotinoOdometryNode::timer_callback, this));
}

RobotinoOdometryNode::~RobotinoOdometryNode()
{
}

void RobotinoOdometryNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	odometry_.setComId( com_.id() );

	com_.connectToServer( false );
}

void RobotinoOdometryNode::timer_callback()
{
	builtin_interfaces::msg::Time curr_time = now();
	odometry_.setTimeStamp(curr_time);

	com_.processEvents();
}
