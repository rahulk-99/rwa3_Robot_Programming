//@pragma once
#ifndef BOT_SEQUENCE_HPP
#define BOT_SEQUENCE_HPP

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>

class BotSequence: public rclcpp::Node 
{
public:
    BotSequence(std::string node_name) : rclcpp::Node(node_name),
            action_flag_(MOVE_FORWARD),     // Initialize action flag
            linear_velocity_(0.5),          // Example values
            angular_velocity_(0.3),
            target_distance_(10.0),  // Example distance for moving forward
            current_distance_(0.0),
            target_angle_(90.0),    // Example angle for rotation
            current_angle_(0.0)
    {
        // Initialize velocity publisher 
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

        // Initialize odometry subscriber 
        odometry_subscriber_ = this->create_subscription<nav_msgs::msg::Odometry>("odom", 10, std::bind(&BotSequence::odom_callback, this, std::placeholders::_1));

        // Set up control timer with a 500 ms period
        control_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&BotSequence::bot_control, this));
        
        
    }
    

private:

    // Enum for robot actions
    enum ActionFlag { MOVE_FORWARD, ROTATE, STOP };
    // Current action
    ActionFlag action_flag_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odometry_subscriber_;
    
    // Timer for periodic control
    rclcpp::TimerBase::SharedPtr control_timer_;

    // Robot state variables
    double linear_velocity_;   // Linear velocity for forward movement
    double angular_velocity_;  // Angular velocity for rotation
    double target_distance_;   // Target distance for forward movement
    double current_distance_;  // Current distance traveled
    double target_angle_;      // Target angle for rotation (degrees)
    double current_angle_;     // Current angle of rotation (degrees)


    void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg);
    void bot_control();

};

#endif // BOT_SEQUENCE_HPP