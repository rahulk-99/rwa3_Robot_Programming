#include "rclcpp/rclcpp.hpp"
#include "waypoint_publisher.hpp"
#include "waypoint_reacher.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    // Creating both nodes
    auto waypoint_publisher = std::make_shared<WaypointPublisher>();
    auto waypoint_reacher = std::make_shared<WaypointReacher>();

    // Creating a single-thread executor
    rclcpp::executors::SingleThreadedExecutor executor;

    // Adding both nodes to the executor
    executor.add_node(waypoint_publisher);
    executor.add_node(waypoint_reacher);

    // Spin the executor
    executor.spin();
    rclcpp::shutdown();
}