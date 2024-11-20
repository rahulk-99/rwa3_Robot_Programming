//@pragma once
#ifndef BOT_SEQUENCE_HPP
#define BOT_SEQUENCE_HPP

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>

class BotSequence: public rclcpp::Node {

public:
    BotSequence();

private:
    void timer_callback();
    void odometry_callback(const nav_msgs::msg::Odometry::SharedPtr msg);

    enum Action { MOVE_FORWARD, ROTATE, STOP };
    Action current_action_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odometry_subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;

    double target_distance_;
    double current_distance_;
    double target_angle_;
    double current_angle_;
    double linear_velocity_;
    double angular_velocity_;
};

#endif // BOT_SEQUENCE_HPP