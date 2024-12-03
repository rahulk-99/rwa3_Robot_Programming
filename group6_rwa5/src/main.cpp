#include "rclcpp/rclcpp.hpp"
#include "waypoint_publisher.hpp"

int main(int argc, char **argv) {
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);

    // Create an instance of the WaypointPublisher node
    auto waypoint_publisher = std::make_shared<WaypointPublisher>();

    // Spin the node to keep it running and processing callbacks
    rclcpp::spin(waypoint_publisher);

    // Shutdown the ROS2 system
    rclcpp::shutdown();

    return 0;
}
