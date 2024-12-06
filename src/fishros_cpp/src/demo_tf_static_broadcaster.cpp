//
// Created by lining on 12/6/24.
//

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"//提供消息接口
#include "tf2/LinearMath/Quaternion.h"//提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"//消息转换函数
#include "tf2_ros/static_transform_broadcaster.h"//静态坐标广播器

class StaticTFBroadcaster : public rclcpp::Node {
private:
    //静态广播器
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> _broadcaster;
public:
    StaticTFBroadcaster() : rclcpp::Node("StaticTFBroadcaster") {
        _broadcaster = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        //只发布一次
        publish_tf();
    }

    //发布函数
    void publish_tf() {
        geometry_msgs::msg::TransformStamped transform;
        transform.header.stamp = get_clock()->now();
        transform.header.frame_id = "map";
        transform.child_frame_id = "target_point";//(5.0,3.0,0.0    0,0,60)
        transform.transform.translation.x = 5.0;
        transform.transform.translation.y = 3.0;
        transform.transform.translation.z = 0.0;
        //欧拉角转四元数
        tf2::Quaternion q;
        q.setRPY(0, 0, 60 * M_PI / 180);
        transform.transform.rotation = tf2::toMsg(q);
        this->_broadcaster->sendTransform(transform);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<StaticTFBroadcaster>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

