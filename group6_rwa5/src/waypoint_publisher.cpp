#include "waypoint_publisher.hpp"

void WaypointPublisher::publish_waypoints() {

    if (index_ < 4 && ready_to_publish_) {
        publisher_->publish(waypoints_[index_]);            //it will publish 1st waypoint whihc is starting state because ready_to_publish_ is initialised with true
        RCLCPP_INFO(this->get_logger(), "Publishing waypoint %zu: x=%.2f, y=%.2f, θ=%.2f, Tolerance: %d",
                    index_,
                    waypoints_[index_].waypoint.x,
                    waypoints_[index_].waypoint.y,
                    waypoints_[index_].waypoint.theta,
                    waypoints_[index_].tolerance);
        ready_to_publish_ = false;                  // Making ready to publish false so that it will check for true condition 
                                                    // for publishing next waypoints through callback_waypoint
    }
}

void WaypointPublisher::callback_waypoint_publisher(const std_msgs::msg::Bool::SharedPtr msg) {
    if (msg->data && index_ < 4) {
        ++index_;
        ready_to_publish_ = true;
        publish_waypoints();
    } else if (index_ >= 4) {
        RCLCPP_INFO(this->get_logger(), "All waypoints published. Shutting down.");
        rclcpp::shutdown();
    }
}
