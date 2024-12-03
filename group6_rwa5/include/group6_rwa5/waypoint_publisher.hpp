#pragma once

#include <rclcpp/rclcpp.hpp>
#include "bot_waypoint_msgs/msg/bot_waypoint.hpp"
#include <std_msgs/msg/bool.hpp>
#include <array>


class WaypointPublisher : public rclcpp::Node {
public:
    WaypointPublisher()
        : Node("waypoint_publisher"), index_{0}, ready_to_publish_{true} {

        publisher_ = this->create_publisher<bot_waypoint_msgs::msg::BotWaypoint>("bot_waypoint", 10);
        subscriber_ = this->create_subscription<std_msgs::msg::Bool>(
            "next_waypoint", 10, std::bind(&WaypointPublisher::callback_waypoint_publisher, this, std::placeholders::_1));

        // Initialize waypoints
        waypoints_[0].waypoint = {0.0, 0.0, 0.0};
        waypoints_[0].tolerance = bot_waypoint_msgs::msg::BotWaypoint::SMALL; // Starting point
        waypoints_[1].waypoint = {4.0, 4.0, 1.57};
        waypoints_[1].tolerance = bot_waypoint_msgs::msg::BotWaypoint::SMALL;
        waypoints_[2].waypoint = {4.0, -4.0, 3.14};
        waypoints_[2].tolerance = bot_waypoint_msgs::msg::BotWaypoint::MEDIUM;
        waypoints_[3].waypoint = {-4.0, 4.0, -3.14};
        waypoints_[3].tolerance = bot_waypoint_msgs::msg::BotWaypoint::LARGE;

        publish_waypoints();
    }

private:
    void publish_waypoints();
    void callback_waypoint_publisher(const std_msgs::msg::Bool::SharedPtr msg);

    rclcpp::Publisher<bot_waypoint_msgs::msg::BotWaypoint>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscriber_;

    std::array<bot_waypoint_msgs::msg::BotWaypoint, 4> waypoints_; // Updated to match 4 waypoints, including home state
    size_t index_;
    bool ready_to_publish_;
};
