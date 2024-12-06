//
// Created by lining on 12/6/24.
//

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"//提供消息接口
#include "tf2/LinearMath/Quaternion.h"//提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"//消息转换函数
#include "tf2_ros/transform_listener.h"//tf监听类
#include "tf2/utils.h"
#include "tf2_ros/buffer.h"
#include <chrono>

using namespace std::chrono_literals;

class TFListener : public rclcpp::Node {
private:
    //静态广播器
    std::shared_ptr<tf2_ros::Buffer> buffer;
    std::shared_ptr<tf2_ros::TransformListener> _listener;
    rclcpp::TimerBase::SharedPtr _timer;
public:
    TFListener() : rclcpp::Node("TF_Listener") {
        buffer = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        buffer->setUsingDedicatedThread(true);
        _listener = std::make_shared<tf2_ros::TransformListener>(*buffer, this, false);
        _timer = this->create_wall_timer(1s, std::bind(&TFListener::getTransform, this));
    }

    void getTransform() {
        //buffer 查询坐标关系
        try {
            const auto transform = buffer->lookupTransform("base_link", "target_point",
                                                           tf2::TimePointZero);
            //获取查询结果
            auto translation = transform.transform.translation;
            auto rotation = transform.transform.rotation;
            //四元数转欧拉角
            double y, p, r;
            tf2::getEulerYPR(rotation, y, p, r);
            RCLCPP_INFO(get_logger(), "平移:%f,%f,%f", translation.x, translation.y, translation.z);
            RCLCPP_INFO(get_logger(), "旋转:%f,%f,%f", y, p, r);

        } catch (const std::exception &e) {
            RCLCPP_WARN(get_logger(), e.what());
        }
    }

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TFListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}