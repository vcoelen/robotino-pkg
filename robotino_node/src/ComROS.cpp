/*
 * ComROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "ComROS.h"
#include <sstream>

ComROS::ComROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
}

ComROS::~ComROS()
{
}

void ComROS::setName( const std::string& name )
{
	name_ = name;
}

void ComROS::errorEvent( const char* errorString )
{
	std::ostringstream os;
	os << name_ << " : " << errorString;

	RCLCPP_ERROR(node_->get_logger(), os.str().c_str() );
}

void ComROS::connectedEvent()
{
	std::ostringstream os;
	os << name_ << " connected to Robotino.";
	RCLCPP_INFO(node_->get_logger(), os.str().c_str() );
}

void ComROS::connectionClosedEvent()
{
	std::ostringstream os;
	os << name_ << " disconnected from Robotino.";
	RCLCPP_INFO(node_->get_logger(), os.str().c_str() );
}
