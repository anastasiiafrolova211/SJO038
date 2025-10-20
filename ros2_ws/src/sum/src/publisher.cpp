#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("publisher");
    auto publisher = node->create_publisher<std_msgs::msg::Int32>("sum", 10);
    std_msgs::msg::Int32 message;
    auto sum_value = 0;
    rclcpp::WallRate loop_rate(500ms);

    while (rclcpp::ok()){
        message.data = sum_value++;
        publisher->publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}

