#include "bot_sequence.hpp"
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

// Odometry callback function
void BotSequence::odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    // Extract position and orientation from odometry message
    auto position = msg->pose.pose.position;
    double roll, pitch, yaw;

    // Convert quaternion to roll, pitch, yaw
    tf2::Quaternion quaternion(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w
    );
    tf2::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);

    // Update current distance and angle
    current_distance_ = std::sqrt(std::pow(position.x, 2) + std::pow(position.y, 2));
    current_angle_ = yaw * 180.0 / M_PI; // Convert radians to degrees
}

// Control loop executed every 500 ms
void BotSequence::bot_control() {
    auto message = geometry_msgs::msg::Twist(); // Create velocity command message

    if (action_flag_ == MOVE_FORWARD) {
        if (current_distance_ < target_distance_) {
            // Move forward
            message.linear.x = linear_velocity_;
            message.angular.z = 0.0;
        } else {
            // Stop after reaching target distance and set next action
            message.linear.x = 0.0;
            action_flag_ = ROTATE;
            current_distance_ = 0.0;  // Reset distance

            // Update the target distance for the next step (if needed)
            if (target_distance_ == 10.0)
            {
                target_distance_ = 5.0; // Move next to 5 meters
                message.linear.y = linear_velocity_;
            }
            else if (target_distance_ == 5.0)
            {
                target_distance_ = 10.0; // Move next to 10 meters
            }
            else
            {
                action_flag_ = STOP; // Finish sequence and stop
            }
        }
    } else if (action_flag_ == ROTATE) {
        if (current_angle_ < target_angle_) {
            // Rotate
            message.linear.x = 0.0;
            message.angular.z = angular_velocity_;
        } else {
            // Stop rotation after reaching target angle
            message.angular.z = 0.0;
            action_flag_ = MOVE_FORWARD; // Set next action
            current_angle_ = 0.0;  // Reset angle

             // Update the target angle for the next rotation step
            if (target_angle_ == 90.0)
            {
                target_angle_ = 45.0; // Next rotation to 45 degrees
            }
            else if (target_angle_ == 45.0)
            {
                target_angle_ = 0.0; // No rotation needed after this
            }
        }
    } else if (action_flag_ == STOP) {
        // Shut down the robot after completing all actions
        message.linear.x = 0.0;
        message.angular.z = 0.0;
        velocity_publisher_->publish(message);  // Publish stop command

        // Shutdown node
        rclcpp::shutdown();
    }

    // Publish velocity command
    velocity_publisher_->publish(message);
}
