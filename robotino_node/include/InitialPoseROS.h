#ifndef INITIALPOSEROS_H_
#define INITIALPOSEROS_H_

#include <memory>

#include "rec/robotino/api2/InitialPose.h"
#include "transform.h"
#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/pose with_covariance_stamped.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf/transform_listener.hpp>

class InitialPoseROS: public rec::robotino::api2::InitialPose
{
public:
	InitialPoseROS(std::shared_ptr<rclcpp::Node> node);
	~InitialPoseROS();

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_sub_;

	rclcpp::Publisher<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr initialPose_pub_;

	geometry_msgs::msg::PoseWithCovarianceStamped initialPose_msg_;

	void initialPoseEvent(float x,float y,double r);

	void mapCallback(const nav_msgs::msg::OccupancyGrid::SharedPtr occupancyGrid);

	MapInfo* mapInfo_;
};

#endif /* INITIALPOSEROS_H_ */
