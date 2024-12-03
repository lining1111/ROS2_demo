//
// Created by lining on 12/2/24.
//
#include <cstdio>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std;

class NovelPubNode:public rclcpp::Node{
private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;
    atomic_int count;

    void timer_callback(){
        std_msgs::msg::String msg;
        msg.data = "hello "+ to_string(count);
        RCLCPP_INFO(this->get_logger(),"Novel pub "+ msg.data);
        pub->publish(msg);
        count++;
    }

public:
    NovelPubNode():Node("NovelPubNode"){
        RCLCPP_INFO(this->get_logger(),"NovelPubNode 启动");
        pub = create_publisher<std_msgs::msg::String>("Novel",5);
        timer = create_wall_timer(std::chrono::seconds(5),std::bind(&NovelPubNode::timer_callback,this));
    }


};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = make_shared<NovelPubNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}