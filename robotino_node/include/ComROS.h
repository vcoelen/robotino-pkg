/*
 * ComROS.h
 *
 *  Created on: 06.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef COMROS_H_
#define COMROS_H_

#include <memory>
#include <string>

#include "rec/robotino/api2/Com.h"

#include "rclcpp/rclcpp.hpp"

class ComROS: public rec::robotino::api2::Com
{
public:
	ComROS(std::shared_ptr<rclcpp::Node> node);
	~ComROS();

	void setName( const std::string& name );

private:
	std::string name_;

	std::shared_ptr<rclcpp::Node> node_;

	void errorEvent( const char* errorString );
	void connectedEvent();
	void connectionClosedEvent();
};

#endif /* COMROS_H_ */
