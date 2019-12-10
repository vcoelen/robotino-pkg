/*
 * EncoderInputROS.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ENCODERINPUTROS_H_
#define ENCODERINPUTROS_H_

#include <memory>

#include "rec/robotino/api2/EncoderInput.h"

#include "rclcpp/rclcpp.hpp"
#include "robotino_msgs/msg/encoder_readings.hpp"
#include "robotino_msgs/srv/set_encoder_position.hpp"


class EncoderInputROS: public rec::robotino::api2::EncoderInput
{
public:
	EncoderInputROS(std::shared_ptr<rclcpp::Node> node);
	~EncoderInputROS();

	void setTimeStamp(builtin_interfaces::msg::Time stamp);

private:
	std::shared_ptr<rclcpp::Node> node_;

	rclcpp::Publisher<robotino_msgs::msg::EncoderReadings>::SharedPtr encoder_pub_;

	rclcpp::Service<robotino_msgs::srv::SetEncoderPosition>::SharedPtr encoder_position_server_;

	robotino_msgs::msg::EncoderReadings encoder_msg_;

	builtin_interfaces::msg::Time stamp_;

	void readingsChangedEvent( int velocity, int position, float current );

	bool setEncoderPositionService(
		const std::shared_ptr<rmw_request_id_t> request_header,
		const std::shared_ptr<robotino_msgs::srv::SetEncoderPosition::Request> req,
		const std::shared_ptr<robotino_msgs::srv::SetEncoderPosition::Response> res);
};

#endif /* ENCODERINPUTROS_H_ */
