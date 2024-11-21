#include "rclcpp/rclcpp.hpp"
#include "bot_sequence.hpp"

int main(int argc, char * argv[])
{
    // Initialize the ROS2 system
    rclcpp::init(argc, argv);

    // Create the node with the name "bot_sequence"
    auto bot_sequence = std::make_shared<BotSequence>("bot_sequence");

    // Spin the node to process incoming messages and keep it alive
    rclcpp::spin(bot_sequence);

    // Shutdown the ROS2 system after execution is complete
    rclcpp::shutdown();
    return 0;
}
