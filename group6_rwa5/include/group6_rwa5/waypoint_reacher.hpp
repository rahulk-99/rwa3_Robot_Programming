#pragma once

#include <cmath>
#include <geometry_msgs/msg/twist.hpp>
#include "bot_waypoint_msgs/msg/bot_waypoint.hpp"
#include <std_msgs/msg/bool.hpp>
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

class WaypointReacher : public rclcpp::Node {
public:
    WaypointReacher()
        : Node("waypoint_reacher"), waypoint_reached_{false} {
        // Subscribing bot_waypoint topic to get waypoint information
        reacher_subscription_ = this->create_subscription<bot_waypoint_msgs::msg::BotWaypoint>(
            "bot_waypoint", 10, std::bind(&WaypointReacher::waypoint_callback_reacher, this, std::placeholders::_1));
        
        // Publisher for velocity commands
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        // Subscriber for odometry
        odom_subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom", 10, std::bind(&WaypointReacher::odom_callback, this, std::placeholders::_1));

        // Publishing to next_waypoint topic for next waypoint
        next_waypoint_publisher_ = this->create_publisher<std_msgs::msg::Bool>("next_waypoint", 10);

        // Controller gains and tolerances
        kp_distance_ = 0.5;
        kp_angle_ = 2.0;

        RCLCPP_INFO_STREAM(this->get_logger(), output_yellow("== waypoint_reacher node Started =="));
    }

private:
    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg);
    void waypoint_callback_reacher(const bot_waypoint_msgs::msg::BotWaypoint::SharedPtr msg);
    void control_loop();
    void publish_velocity(double linear, double angular);
    double normalize_angle(double angle);

    // Subscriber and Publisher
    rclcpp::Subscription<bot_waypoint_msgs::msg::BotWaypoint>::SharedPtr reacher_subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_subscription_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr next_waypoint_publisher_;


    double goal_x_;
    double goal_y_;
    double goal_theta_;
    double kp_distance_;
    double kp_angle_;
    // double tolerance_value_;
    bool waypoint_reached_;

    // Current state of the robot
    double current_x_;
    double current_y_;
    double current_theta_;
    double roll_;
    double pitch_;
};
