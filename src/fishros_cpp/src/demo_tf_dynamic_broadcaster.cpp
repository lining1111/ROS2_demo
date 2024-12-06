//
// Created by lining on 12/6/24.
//

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"//提供消息接口
#include "tf2/LinearMath/Quaternion.h"//提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"//消息转换函数
#include "tf2_ros/transform_broadcaster.h"//动态坐标广播器
#include <chrono>

using namespace std::chrono_literals;

class DynamicTFBroadcaster : public rclcpp::Node {
private:
    //静态广播器
    std::shared_ptr<tf2_ros::TransformBroadcaster> _broadcaster;
    rclcpp::TimerBase::SharedPtr _timer;
public:
    DynamicTFBroadcaster() : rclcpp::Node("TFBroadcaster") {
        _broadcaster = std::make_shared<tf2_ros::TransformBroadcaster>(this);
        _timer = this->create_wall_timer(100ms,std::bind(&DynamicTFBroadcaster::publish_tf,this));
    }

    //发布函数
    void publish_tf() {
        geometry_msgs::msg::TransformStamped transform;
        transform.header.stamp = get_clock()->now();
        transform.header.frame_id = "map";
        transform.child_frame_id = "base_link";//(2.0,3.0,0.0    0,0,30)
        transform.transform.translation.x = 2.0;
        transform.transform.translation.y = 3.0;
        transform.transform.translation.z = 0.0;
        //欧拉角转四元数
        tf2::Quaternion q;
        q.setRPY(0, 0, 30 * M_PI / 180);
        transform.transform.rotation = tf2::toMsg(q);
        this->_broadcaster->sendTransform(transform);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DynamicTFBroadcaster>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}