/*
 * RobotinoNode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include <sstream>
#include <chrono>

#include "RobotinoLaserRangeFinderNode.h"

using namespace std::chrono_literals;

RobotinoLaserRangeFinderNode::RobotinoLaserRangeFinderNode() :
	Node("robotino_laserrangefinder_node"),
	com_(this->shared_from_this()),
	laser_range_finder_(this->shared_from_this())
{
	declare_parameter("hostname", "IP address of the robot");
    if(!get_parameter("hostname", hostname_))
    {
        hostname_ = "172.26.1.1";
    }

	declare_parameter("laserRangeFinderNumber", "");
    if(!get_parameter("laserRangeFinderNumber_", laserRangeFinderNumber_))
    {
        laserRangeFinderNumber_ = 0;
    }


	std::ostringstream os;
	os << "LaserRangeFinder" << laserRangeFinderNumber_;
	com_.setName( os.str() );

	initModules();
	timer_ = this->create_wall_timer( 33ms, std::bind(&RobotinoLaserRangeFinderNode::timer_callback, this));
}

RobotinoLaserRangeFinderNode::~RobotinoLaserRangeFinderNode()
{
}

void RobotinoLaserRangeFinderNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	laser_range_finder_.setComId( com_.id() );

	// Set the LaserRangeFinder numbers
	laser_range_finder_.setNumber( laserRangeFinderNumber_ );

	com_.connectToServer( false );
}

void RobotinoLaserRangeFinderNode::timer_callback()
{
	builtin_interfaces::msg::Time curr_time = now();
	laser_range_finder_.setTimeStamp(curr_time);

	com_.processEvents();

}
