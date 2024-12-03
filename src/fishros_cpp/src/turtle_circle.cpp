//
// Created by lining on 12/3/24.
//

#include <cstdio>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono_literals;

class TurtleCircleNode : public rclcpp::Node {
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;
    void timer_cb(){
        auto msg = geometry_msgs::msg::Twist();
        msg.linear.x = 1.0;
        msg.angular.z = 0.5;
        pub->publish(msg);
    }

public:
    explicit TurtleCircleNode() : rclcpp::Node("TurtleCircleNode") {
        pub = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
        timer = create_wall_timer(1000ms,std::bind(&TurtleCircleNode::timer_cb,this));
    }

};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node = make_shared<TurtleCircleNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
