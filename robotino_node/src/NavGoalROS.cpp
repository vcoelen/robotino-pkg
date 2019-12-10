#include "NavGoalROS.h"

#include <tf2/LinearMath/Quaternion.h>

using std::placeholders::_1;

NavGoalROS::NavGoalROS(std::shared_ptr<rclcpp::Node> node) : node_(node)
{
	navGoal_pub_ = node_->create_publisher<geometry_msgs::msg::PoseStamped>("move_base_simple/goal", 1); //removed latching TODO (vcoelen) has to be fixed

	mapInfo_ = NULL;
	map_sub_ = node_->create_subscription<nav_msgs::msg::OccupancyGrid>("map", 1, std::bind(&NavGoalROS::mapCallback, this, _1));

}

NavGoalROS::~NavGoalROS()
{


}

void NavGoalROS:: navGoalEvent(float x,float y,double r)
{
	if(mapInfo_)
	{
		navGoal_msg_.pose.position.x = ( -mapInfo_->resolution * (x + mapInfo_->offset[0] ) );
		navGoal_msg_.pose.position.y = ( mapInfo_->resolution * ( y + mapInfo_->offset[1] ) );

		navGoal_msg_.pose.position.z = 0;

		double rot = deg2rad( r );
		double rx = cos( rot );
		double ry = sin( rot );
		rot = atan2( ry, -rx );

		tf2::Quaternion q;
	    quat.setRPY(0.0, 0.0, rot);
		navGoal_msg_.pose.orientation.x = q.x();
		navGoal_msg_.pose.orientation.y = q.y();
		navGoal_msg_.pose.orientation.z = q.z();
		navGoal_msg_.pose.orientation.w = q.w();

		navGoal_msg_.header.frame_id = mapInfo_->frame_id;
		navGoal_msg_.header.stamp = node_->now();

		navGoal_pub_->publish(navGoal_msg_);

	}
}

void NavGoalROS::mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr occupancyGrid)
{
	if(mapInfo_)
	{
		delete mapInfo_;
	}
	mapInfo_ = new MapInfo(occupancyGrid, occupancyGrid.header.frame_id);
}
