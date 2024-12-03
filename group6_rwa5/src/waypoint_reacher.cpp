// #include "waypoint_reacher.hpp"

// WaypointReacher::WaypointReacher()
//     : Node("waypoint_reacher"), waypoint_reached_(false) {
//     waypoint_subscriber_ = this->create_subscription<bot_waypoint_msgs::msg::BotWaypoint>(
//         "bot_waypoint", 10,
//         [this](const bot_waypoint_msgs::msg::BotWaypoint::SharedPtr msg) {
//             waypoint_callback(msg);
//         });
//     next_waypoint_publisher_ = this->create_publisher<std_msgs::msg::Bool>("next_waypoint", 10);
// }

// void WaypointReacher::waypoint_callback(const bot_waypoint_msgs::msg::BotWaypoint::SharedPtr msg) {
//     navigate_to_waypoint(msg->waypoint, msg->tolerance / 10.0);
//     waypoint_reached_ = true;

//     if (waypoint_reached_) {
//         auto signal = std::make_shared<std_msgs::msg::Bool>();
//         signal->data = true;
//         next_waypoint_publisher_->publish(*signal);
//     }
// }

// void WaypointReacher::navigate_to_waypoint(const geometry_msgs::msg::Pose2D &pose, double tolerance) {
//     // Implement proportional control for (x, y) and orientation adjustment
//     RCLCPP_INFO(this->get_logger(), "Navigating to waypoint (x: %.2f, y: %.2f, θ: %.2f)", pose.x, pose.y, pose.theta);
//     // Logic for moving the robot within the given tolerance
// }
