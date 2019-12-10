/*
 * GrapplerROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "GrapplerROS.h"

using std::placeholders::_1;

GrapplerROS::GrapplerROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	grappler_readings_pub_ = node_->create_publisher<robotino_msgs::msg::GrapplerReadings>("grappler_readings", 1); //removed latching TODO (vcoelen) has to be fixed
	grappler_store_pub_ = node_->create_publisher<robotino_msgs::msg::GrapplerReadings>("grappler_store_positions", 1); // removed latching=false TODO (vcoelen) has to be fixed
	grappler_axes_sub_ = node_->create_subscription<robotino_msgs::msg::SetGrapplerAxes>("set_grappler_axes", 1, std::bind(&GrapplerROS::setGrapplerAxes, this, _1));
	grappler_axis_sub_ = node_->create_subscription<robotino_msgs::msg::SetGrapplerAxis>("set_grappler_axis", 1, std::bind(&GrapplerROS::setGrapplerAxis, this, _1));
}

GrapplerROS::~GrapplerROS()
{




}

void GrapplerROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void GrapplerROS::readingsEvent( const rec::robotino::api2::GrapplerReadings& readings )
{
	unsigned int numServos = readings.numServos;

	// Build the GrapplerReadings msg
	grappler_readings_msg_.stamp 		= stamp_;
	grappler_readings_msg_.seq 			= readings.sequenceNumber;
	grappler_readings_msg_.num_servos 	= numServos;
	grappler_readings_msg_.torque_enabled = readings.isTorqueEnabled;

	grappler_readings_msg_.angles.resize( numServos );
	grappler_readings_msg_.errors.resize( numServos );
	grappler_readings_msg_.channels.resize( numServos );
	grappler_readings_msg_.ids.resize( numServos );
	grappler_readings_msg_.cw_axes_limits.resize( numServos );
	grappler_readings_msg_.ccw_axes_limits.resize( numServos );

	for( unsigned int i = 0; i < numServos; ++i)
	{
		grappler_readings_msg_.angles[i] 		= readings.angles[i];
		grappler_readings_msg_.errors[i] 		= readings.errors[i];
		grappler_readings_msg_.channels[i] 		= readings.channels[i];
		grappler_readings_msg_.ids[i] 			= readings.ids[i];
		grappler_readings_msg_.cw_axes_limits[i] 	= readings.cwAxesLimits[i];
		grappler_readings_msg_.ccw_axes_limits[i] = readings.ccwAxesLimits[i];
	}

	// Publish the msg
	grappler_readings_pub_->publish( grappler_readings_msg_ );
}

void GrapplerROS::storePositionsEvent( const rec::robotino::api2::GrapplerReadings& readings )
{
	unsigned int numServos = readings.numServos;

	// Build the GrapplerReadings msg
	grappler_store_msg_.stamp 		= stamp_;
	grappler_store_msg_.seq 		= readings.sequenceNumber;
	grappler_store_msg_.num_servos 	= numServos;
	grappler_store_msg_.torque_enabled = readings.isTorqueEnabled;

	grappler_store_msg_.angles.resize( numServos );
	grappler_store_msg_.errors.resize( numServos );
	grappler_store_msg_.channels.resize( numServos );
	grappler_store_msg_.ids.resize( numServos );
	grappler_store_msg_.cw_axes_limits.resize( numServos );
	grappler_store_msg_.ccw_axes_limits.resize( numServos );

	for( unsigned int i = 0; i < numServos; ++i)
	{
		grappler_store_msg_.angles[i] 		= readings.angles[i];
		grappler_store_msg_.errors[i] 		= readings.errors[i];
		grappler_store_msg_.channels[i] 		= readings.channels[i];
		grappler_store_msg_.ids[i] 			= readings.ids[i];
		grappler_store_msg_.cw_axes_limits[i] 	= readings.cwAxesLimits[i];
		grappler_store_msg_.ccw_axes_limits[i] 	= readings.ccwAxesLimits[i];
	}

	// Publish the msg
	grappler_store_pub_->publish( grappler_store_msg_ );
}

void GrapplerROS::setGrapplerAxes( const robotino_msgs::msg::SetGrapplerAxes::SharedPtr msg)
{
	int numAngles = msg->angles.size();
	int numVelocities = msg->velocities.size();
	if( numAngles == numVelocities && numAngles > 0 )
	{
		float angles[numAngles];
		float velocities[numVelocities];

		memcpy(angles, msg->angles.data(), numAngles * sizeof(float) );
		memcpy(velocities, msg->velocities.data(), numVelocities * sizeof(float) );

		setAxes( angles, numAngles, velocities, numVelocities);
	}
}

void GrapplerROS::setGrapplerAxis( const robotino_msgs::msg::SetGrapplerAxis::SharedPtr msg)
{
	int axis = msg->axis;
	int angle = msg->angle;
	int velocity = msg->velocity;
	setAxis( axis, angle, velocity );
}
