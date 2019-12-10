/*
 * CameraROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "CameraROS.h"
#include <sensor_msgs/fill_image.hpp>


CameraROS::CameraROS(std::shared_ptr<rclcpp::Node> node) :
	node_(node),
	img_transport_(node_)
{
}

CameraROS::~CameraROS()
{

}

void CameraROS::setNumber( int number )
{
	std::stringstream topic;

	if( number == 0)
		topic << "image_raw";
	else
		topic << "image_raw" << number;

	streaming_pub_ = img_transport_.advertiseCamera(topic.str(), 1); // removed latching=false TODO (vcoelen) has to be fixed

	setCameraNumber( number );
}

void CameraROS::setTimeStamp(builtin_interfaces::msg::Time stamp)
{
	stamp_ = stamp;
}

void CameraROS::imageReceivedEvent(
		const unsigned char* data,
		unsigned int dataSize,
		unsigned int width,
		unsigned int height,
		unsigned int step )
{
	// Build the Image msg
	img_msg_.header.stamp = stamp_;
	sensor_msgs::fillImage(img_msg_, "rgb8", height, width, step, data);

	// Build the CameraInfo msg
	cam_info_msg_.header.stamp = stamp_;
	cam_info_msg_.height = height;
	cam_info_msg_.width = width;

	// Publish the Image & CameraInfo msgs
	streaming_pub_.publish(img_msg_, cam_info_msg_);

}
