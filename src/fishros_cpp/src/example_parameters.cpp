//
// Created by lining on 12/5/24.
//
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "rcutils/logging.h"

/*
    # declare_parameter            声明和初始化一个参数
    # describe_parameter(name)  通过参数名字获取参数的描述
    # get_parameter                通过参数名字获取一个参数
    # set_parameter                设置参数的值
*/

class ParametersBasicNode : public rclcpp::Node {
public:
    explicit ParametersBasicNode(std::string name) : Node(name) {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
        this->declare_parameter("rcl_log_level", 0);     /*声明参数*/
        this->get_parameter("rcl_log_level", log_level); /*获取参数*/
        /*设置日志级别*/
        rcutils_logging_set_logger_level(get_logger().get_name(),log_level);
        using namespace std::literals::chrono_literals;
//        timer_ = this->create_wall_timer(
//                500ms, std::bind(&ParametersBasicNode::timer_callback, this));
        this->add_on_set_parameters_callback(std::bind(&ParametersBasicNode::parameters_cb, this,std::placeholders::_1));
    }
private:
    int log_level;
    rclcpp::TimerBase::SharedPtr timer_;
    void timer_callback() {
        this->get_parameter("rcl_log_level", log_level); /*获取参数*/
        /*设置日志级别*/
        rcutils_logging_set_logger_level(get_logger().get_name(),log_level);
        std::cout<<"======================================================"<<std::endl;
        RCLCPP_DEBUG(this->get_logger(), "我是DEBUG级别的日志，我被打印出来了!");
        RCLCPP_INFO(this->get_logger(), "我是INFO级别的日志，我被打印出来了!");
        RCLCPP_WARN(this->get_logger(), "我是WARN级别的日志，我被打印出来了!");
        RCLCPP_ERROR(this->get_logger(), "我是ERROR级别的日志，我被打印出来了!");
        RCLCPP_FATAL(this->get_logger(), "我是FATAL级别的日志，我被打印出来了!");
    }

    rcl_interfaces::msg::SetParametersResult parameters_cb(const std::vector<rclcpp::Parameter> &params){
        rcl_interfaces::msg::SetParametersResult ret;
        for (auto iter:params) {
            if (iter.get_name() == "rcl_log_level"){
                this->log_level = iter.get_value<int>();
                RCLCPP_INFO(get_logger(),"rcl_log_level set %d",log_level);
                ret.successful = true;
                ret.reason="set success";
            }
        }
        return ret;
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<ParametersBasicNode>("parameters_basic");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}