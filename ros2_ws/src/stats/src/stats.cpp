#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"
#include <iostream>

// subscriber node

int count;
int sum;
float mean;

std::shared_ptr<rclcpp::Publisher<std_msgs::msg::Float32>> publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg){
    count += 1;

    sum += msg->data;
    mean = static_cast<float>(sum) / static_cast<float>(count);
    
    std_msgs::msg::Float32 out_msg;
    out_msg.data = mean;
    publisher->publish(out_msg);
}

int main(int argc, char * argv[]){

    count = 0;

    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("mean");
    auto subscription = node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
    publisher = node->create_publisher<std_msgs::msg::Float32>("mean", 10);
    
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
