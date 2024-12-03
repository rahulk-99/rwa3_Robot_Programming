// #ifndef WAYPOINT_REACHER_HPP
// #define WAYPOINT_REACHER_HPP

// #include "rclcpp/rclcpp.hpp"
// #include "bot_waypoint_msgs/msg/bot_waypoint.hpp"
// #include "geometry_msgs/msg/pose2d.hpp"
// #include "std_msgs/msg/bool.hpp"

// class WaypointReacher : public rclcpp::Node {
// public:
//     WaypointReacher();
// private:
//     void waypoint_callback(const bot_waypoint_msgs::msg::BotWaypoint::SharedPtr msg);
//     void navigate_to_waypoint(const geometry_msgs::msg::Pose2D &pose, double tolerance);

//     rclcpp::Subscription<bot_waypoint_msgs::msg::BotWaypoint>::SharedPtr waypoint_subscriber_;
//     rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr next_waypoint_publisher_;
//     bool waypoint_reached_;
// };

// #endif
