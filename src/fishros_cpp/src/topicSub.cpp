#include <cstdio>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std;

class NovelSubNode:public rclcpp::Node{
private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub;

    void sub_callback(std_msgs::msg::String::SharedPtr msg){
        RCLCPP_INFO(this->get_logger(),"Novel sub "+ msg->data);
    }

public:
    NovelSubNode():Node("NovelSubNode"){
        RCLCPP_INFO(this->get_logger(),"NovelSubNode 启动");
        sub = create_subscription<std_msgs::msg::String>("Novel",5,std::bind(&NovelSubNode::sub_callback,this,std::placeholders::_1));
    }
};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = make_shared<NovelSubNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}