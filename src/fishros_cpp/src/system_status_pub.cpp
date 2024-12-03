//
// Created by lining on 12/3/24.
//
#include "rclcpp/rclcpp.hpp"
#include "fishros_cpp/msg/system_status.hpp"


int main(int argc,char **argv){
    rclcpp::init(argc,argv);

    rclcpp::shutdown();
    return 0;
}