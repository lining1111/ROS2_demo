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

class TurtleControlNode : public rclcpp::Node {
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub;
    double target_x{1.0};
    double target_y{1.0};
    double k{1.0};//比例系数
    double max_speed{3.0};//最大速度


    void sub_cb(const turtlesim::msg::Pose::SharedPtr pose) {
        RCLCPP_INFO(this->get_logger(), "pose:x:%f,y:%f,theta:%f",
                    pose->x, pose->y, pose->theta);
        //1,获取当前的位置
        auto current_x = pose->x;
        auto current_y = pose->y;
        //2.计算当前海龟的位置与目标之前的距离差和角度差
        auto distance = sqrt(
                (target_x - current_x) * (target_x - current_x) + (target_y - current_y) * (target_y - current_y));
        auto angle = atan2((target_y - current_y), (target_x - current_x)) - pose->theta;
        //3.控制策略
        auto msg = geometry_msgs::msg::Twist();
        if (distance > 0.1) {
            if (fabs(angle) > 0.2) {
                msg.angular.z = fabs(angle);
            } else {
                msg.linear.x = k * distance;
            }
        }
        //4.限制最大速度
        if (msg.linear.x > max_speed) {
            msg.linear.x = max_speed;
        }
        pub->publish(msg);
    }

public:
    explicit TurtleControlNode() : rclcpp::Node("TurtleControlNode") {
        pub = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        sub = create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10,
                                                        std::bind(&TurtleControlNode::sub_cb, this,
                                                                  std::placeholders::_1));
    }

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<TurtleControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}