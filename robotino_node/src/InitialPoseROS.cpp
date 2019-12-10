#include "InitialPoseROS.h"

#include <tf2/LinearMath/Quaternion.h>

using std::placeholders::_1;

InitialPoseROS::InitialPoseROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	initialPose_pub_ = node_->create_publisher<geometry_msgs::msg::PoseWithCovarianceStamped>("initialpose", 1); //removed latching TODO (vcoelen) has to be fixed
	mapInfo_ = NULL;
	map_sub_ = node_->create_subscription<nav_msgs::msg::OccupancyGrid>("map", 1, std::bind(&InitialPoseROS::mapCallback, this, _1));

}

InitialPoseROS::~InitialPoseROS()
{
}

void InitialPoseROS:: initialPoseEvent(float x,float y,double r)
{
	if(mapInfo_)
	{
		initialPose_msg_.pose.pose.position.x = ( -mapInfo_->resolution * (x + mapInfo_->offset[0] ) );
		initialPose_msg_.pose.pose.position.y = ( mapInfo_->resolution * ( y + mapInfo_->offset[1] ) );
		initialPose_msg_.pose.pose.position.z = 0;

		double rot = deg2rad( r );
		double rx = cos( rot );
		double ry = sin( rot );
		rot = atan2( ry, -rx );

		tf2::Quaternion q;
		q.setRPY(0.0, 0.0, rot);

		initialPose_msg_.pose.pose.orientation.x = q.x();
		initialPose_msg_.pose.pose.orientation.y = q.y();
		initialPose_msg_.pose.pose.orientation.z = q.z();
		initialPose_msg_.pose.pose.orientation.w = q.w();

		initialPose_msg_.header.frame_id = mapInfo_->frame_id;
		initialPose_msg_.header.stamp = node_->now();

		initialPose_pub_->publish(initialPose_msg_);
	}
}

void InitialPoseROS::mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr occupancyGrid)
{
	if(mapInfo_)
	{
		delete mapInfo_;
	}
	mapInfo_ = new MapInfo(occupancyGrid, occupancyGrid.header.frame_id);
}
