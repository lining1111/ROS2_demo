//
// Created by lining on 12/3/24.
//
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "fishros/msg/system_status.hpp"
#include "../systemStatus/systemStatus.h"

using namespace std;


class SysStatusPub : public rclcpp::Node {
private:
    rclcpp::Publisher<fishros::msg::SystemStatus>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;

    void timer_callback() {
        fishros::msg::SystemStatus msg;
        msg.stamp = this->get_clock()->now();
        msg.host = getuname();
        msg.cpu_percent = cpuUtilizationRatio();
        float memoryTotal = 0.0;
        float memoryAvailble = 0.0;
        if (memoryInfo(memoryTotal, memoryAvailble) == 0) {
            msg.memory_total = memoryTotal;
            msg.memory_available = memoryAvailble;
            if (msg.memory_total != 0) {
                msg.memory_percent = msg.memory_available / msg.memory_total;
            }
        }
        vector<NetInfo> netInfos;
        getNetInfos(netInfos);
        for (auto iter: netInfos) {
            msg.net_recv += iter.receiveBytes;
            msg.net_sent += iter.receiveBytes;
        }
        msg.net_recv /= (1024 * 1024);
        msg.net_sent /= (1024 * 1024);

        RCLCPP_INFO(this->get_logger(), "SysStatusPub pub " + msg.host);
        pub->publish(msg);
    }

public:
    SysStatusPub() : Node("SysStatusPub") {
        RCLCPP_INFO(this->get_logger(), "SysStatusPub 启动");
        pub = create_publisher<fishros::msg::SystemStatus>("sys_status", 10);
        timer = create_wall_timer(std::chrono::seconds(5), std::bind(&SysStatusPub::timer_callback, this));
    }


};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<SysStatusPub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}