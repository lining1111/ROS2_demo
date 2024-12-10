//
// Created by lining on 12/4/24.
//

#include <cstdio>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "fishros/msg/system_status.hpp"

using namespace std;

class SysStatusSub : public rclcpp::Node {
private:
    rclcpp::Subscription<fishros::msg::SystemStatus>::SharedPtr sub;

    void sub_callback(fishros::msg::SystemStatus::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "sys_status sub " + msg->host);
    }

public:
    SysStatusSub() : Node("SysStatusSub") {
        RCLCPP_INFO(this->get_logger(), "SysStatusSub 启动");
        sub = create_subscription<fishros::msg::SystemStatus>("sys_status", 5,
                                                                              std::bind(&SysStatusSub::sub_callback,
                                                                                        this, std::placeholders::_1));
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<SysStatusSub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}