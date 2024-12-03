#include "waypoint_publisher.hpp"

void WaypointPublisher::callback_waypoint(const std_msgs::msg::Bool::SharedPtr msg) {
    // If the received message is 'true' and there are more waypoints to publish
    if (msg->data && index_ < waypoints_.size()) {
        ready_to_publish_ = true; // Allow publishing the next waypoint
        RCLCPP_INFO(this->get_logger(), "Received signal to publish next waypoint.");
    }
}

void WaypointPublisher::publish_waypoints() {
    // Only proceed if ready to publish and there are waypoints left
    if (ready_to_publish_ && index_ < waypoints_.size()) {
        const auto &current_waypoint = waypoints_[index_];

        // Translate the tolerance to allowable distance (1 = 0.1m, 2 = 0.2m, 3 = 0.3m)
        float allowable_distance = static_cast<float>(current_waypoint.tolerance) / 10.0;

        // Log the waypoint details including the allowable distance
        RCLCPP_INFO(this->get_logger(),
                    "Publishing waypoint %zu: x=%.2f, y=%.2f, θ=%.2f, tolerance=%.1f meters",
                    index_,
                    current_waypoint.waypoint.x,
                    current_waypoint.waypoint.y,
                    current_waypoint.waypoint.theta,
                    allowable_distance);

        // Publish the current waypoint
        publisher_->publish(current_waypoint);

        // Move to the next waypoint
        index_++;
        ready_to_publish_ = false; // Prevent continuous publishing
    }
}
