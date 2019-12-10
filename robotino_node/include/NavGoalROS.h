#ifndef NAVGOALROS_H_
#define NAVGOALROS_H_

#include <memory>

#include "rec/robotino/api2/NavGoal.h"
#include "transform.h"
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf/transform_listener.hpp>

class NavGoalROS: public rec::robotino::api2::NavGoal
{
public:
	NavGoalROS(std::shared_ptr<rclcpp::Node> node);
	~NavGoalROS();

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr navGoal_pub_;

	rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_sub_;

	geometry_msgs::msg::PoseStamped navGoal_msg_;

	void navGoalEvent(float x,float y,double r);

	void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr occupancyGrid);

	MapInfo* mapInfo_;
};

#endif /* NAVGOALROS_H_ */
