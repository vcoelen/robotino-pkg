/*
 * LaserRangeFinderROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "LaserRangeFinderROS.h"

LaserRangeFinderROS::LaserRangeFinderROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
}

LaserRangeFinderROS::~LaserRangeFinderROS()
{

}

void LaserRangeFinderROS::setNumber( int number )
{
	std::stringstream topic;

	if( number == 0)
		topic << "scan";
	else
		topic << "scan" << number;

	laser_scan_pub_ = node_->create_publisher<sensor_msgs::msg::LaserScan>(topic.str(), 1); // removed latching=false TODO (vcoelen) has to be fixed

	setLaserRangeFinderNumber( number );
}

void LaserRangeFinderROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void LaserRangeFinderROS::scanEvent(const rec::robotino::api2::LaserRangeFinderReadings &scan)
{
	// Build the LaserScan message
	laser_scan_msg_.header.stamp = stamp_;
	laser_scan_msg_.header.frame_id = "laser_link";

	laser_scan_msg_.angle_min = scan.angle_min;
	laser_scan_msg_.angle_max = scan.angle_max;
	laser_scan_msg_.angle_increment = scan.angle_increment;
	laser_scan_msg_.time_increment = scan.time_increment;
	laser_scan_msg_.scan_time = scan.scan_time;
	laser_scan_msg_.range_min = scan.range_min;
	laser_scan_msg_.range_max = scan.range_max;

	unsigned int numRanges, numIntensities;
	const float* ranges;
	const float* intensities;
	scan.ranges( &ranges, &numRanges );
	scan.intensities( &intensities, &numIntensities );

	laser_scan_msg_.ranges.resize( numRanges );
	laser_scan_msg_.intensities.resize( numIntensities);

	//RCLCPP_INFO(" num intensities: %d num ranges: %d", numIntensities, numRanges );
	if( ranges != NULL )
	{
		memcpy( laser_scan_msg_.ranges.data(), ranges, numRanges * sizeof(float) );
	}

	if( intensities != NULL )
	{
		memcpy( laser_scan_msg_.intensities.data(), intensities, numIntensities * sizeof(float) );
	}

	// Publish the message
	if( numRanges > 0 || numIntensities > 0)
		laser_scan_pub_->publish(laser_scan_msg_);
}
