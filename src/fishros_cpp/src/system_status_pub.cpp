//
// Created by lining on 12/3/24.
//
#include "rclcpp/rclcpp.hpp"
#include "fishros_cpp/msg/system_status.hpp"

class SysStatusPub:public rclcpp::Node{
private:
    rclcpp::Publisher<fishros_cpp::msg::SystemStatus>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;

    void timer_callback(){
        fishros_cpp::msg::SystemStatus msg;

        RCLCPP_INFO(this->get_logger(),"SysStatusPub pub "+ msg.host);
        pub->publish(msg);
    }

public:
    SysStatusPub():Node("SysStatusPub"){
        RCLCPP_INFO(this->get_logger(),"SysStatusPub 启动");
        pub = create_publisher<fishros_cpp::msg::SystemStatus>("Novel",5);
        timer = create_wall_timer(std::chrono::seconds(5),std::bind(&SysStatusPub::timer_callback,this));
    }


};

int main(int argc,char **argv){
    rclcpp::init(argc,argv);

    rclcpp::shutdown();
    return 0;
}