/*
 * RobotinoNode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RobotinoCameraNode.h"
#include <chrono>

#include <sstream>

using namespace std::chrono_literals;

RobotinoCameraNode::RobotinoCameraNode() :
	Node("robotino_laserrangefinder_node"),
	com_(this->shared_from_this()),
	camera_(this->shared_from_this())
{
	declare_parameter("hostname", "IP address of the robot");
    if(!get_parameter("hostname", hostname_))
    {
        hostname_ = "172.26.1.1";
    }

	declare_parameter("cameraNumber", "");
    if(!get_parameter("cameraNumber_", cameraNumber_))
    {
        cameraNumber_ = 0;
    }

	std::ostringstream os;
	os << "Camera" << cameraNumber_;
	com_.setName( os.str() );

	initModules();
	timer_ = this->create_wall_timer( 33ms, std::bind(&RobotinoCameraNode::timer_callback, this));

}

RobotinoCameraNode::~RobotinoCameraNode()
{
}

void RobotinoCameraNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	camera_.setComId( com_.id() );

	// Set the LaserRangeFinder numbers
	camera_.setNumber( cameraNumber_ );

	com_.connectToServer( false );
}

void RobotinoCameraNode::timer_callback()
{

	builtin_interfaces::msg::Time curr_time = now();
	camera_.setTimeStamp(curr_time);

	com_.processEvents();
}
