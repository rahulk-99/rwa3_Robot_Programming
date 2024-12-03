#pragma once

#include <rclcpp/rclcpp.hpp>
#include "bot_waypoint_msgs/msg/bot_waypoint.hpp"
#include <std_msgs/msg/bool.hpp>
#include <array>

class WaypointPublisher : public rclcpp::Node {
public:
    // Constructor
    WaypointPublisher()
        : Node("waypoint_publisher"), index_(0), ready_to_publish_(true) {

        // Create ROS2 publisher
        publisher_ = this->create_publisher<bot_waypoint_msgs::msg::BotWaypoint>("bot_waypoint", 10);

        // Create ROS2 subscriber and bind to the callback function
        subscriber_ = this->create_subscription<std_msgs::msg::Bool>(
            "next_waypoint", 10, std::bind(&WaypointPublisher::callback_waypoint, this, std::placeholders::_1));

        // Defining waypoints (Note: 1st waypoint is assumed to be home position i.e. at 0,0 with 0 rad rotation and will be checked with small tolerance)
        // waypoints_[0] = bot_waypoint_msgs::msg::BotWaypoint{geometry_msgs::msg::Pose2D{0.0, 0.0, 0.0}, 1};
        // waypoints_[1] = bot_waypoint_msgs::msg::BotWaypoint{geometry_msgs::msg::Pose2D{4.0, 4.0, 1.57}, 1}; 
        // waypoints_[2] = bot_waypoint_msgs::msg::BotWaypoint{geometry_msgs::msg::Pose2D{4.0, -4.0, 3.14}, 2};
        // waypoints_[3] = bot_waypoint_msgs::msg::BotWaypoint{geometry_msgs::msg::Pose2D{-4.0, 4.0, -3.14}, 3};

        // Publishing the first waypoint
        publish_waypoints();
    }

private:
    // To publish the next waypoint
    void publish_waypoints();

    // Callback function for the subscriber
    void callback_waypoint(const std_msgs::msg::Bool::SharedPtr msg);

    // Publisher and Subscriber
    rclcpp::Publisher<bot_waypoint_msgs::msg::BotWaypoint>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscriber_;

    std::array<bot_waypoint_msgs::msg::BotWaypoint, 4> waypoints_;  // array of 4 elements defined for waypoints
    size_t index_;                                                  // To tracks current waypoint
    bool ready_to_publish_;                                         // Flag to control publishing behavior
};
