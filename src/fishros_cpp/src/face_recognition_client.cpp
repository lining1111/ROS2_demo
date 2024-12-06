//
// Created by lining on 12/5/24.
//

#include "rclcpp/rclcpp.hpp"
#include "face_recognition/srv/face_detector.hpp"
#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class FaceRecognitionClient : public rclcpp::Node {
private:
    rclcpp::Client<face_recognition::srv::FaceDetector>::SharedPtr _client;
    cv_bridge::CvImagePtr cv_ptr;

    void handle(const std::shared_ptr<face_recognition::srv::FaceDetector::Request> request,
                std::shared_ptr<face_recognition::srv::FaceDetector::Response> response) {
        //将获取的图像通过cvBridge库来转换为opencv识别的
        try {
            cv_ptr = cv_bridge::toCvCopy(request->image);
        } catch (cv_bridge::Exception &e) {
            RCLCPP_ERROR(get_logger(), "Could not convert from %s", request->image.encoding.c_str());
        }
        if (cv_ptr) {

            cv::imshow("receive img", cv_ptr->image);
            auto start_time = this->get_clock()->now().nanoseconds();
            //进行人脸识别

            auto end_time = get_clock()->now().nanoseconds();

            response->use_time = end_time - start_time;

            response->number = 1;
        }

    }

public:
    FaceRecognitionClient() : rclcpp::Node("FaceRecognitionClient") {
        RCLCPP_INFO(get_logger(), "FaceRecognitionClient start");
        _client = create_client<face_recognition::srv::FaceDetector>("face_recognition_srv");

    };

    void send_request(cv::Mat img){
        //1.等待服务上线
        while (!_client->wait_for_service(std::chrono::seconds(1))) {
            //等待时检测rclcpp的状态
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "等待服务的过程中被打断...");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务端上线中");
        }
        // 2.发送异步请求，然后等待返回，返回时调用回调函数
        auto ros2_img = cv_bridge::CvImage(std_msgs::msg::Header(),"bgr8",img).toImageMsg();
        auto request = std::make_shared<face_recognition::srv::FaceDetector::Request>();
        request->image = *ros2_img;

        _client->async_send_request(
                request, std::bind(&FaceRecognitionClient::response_cb, this,
                                   std::placeholders::_1));
    }



    void response_cb(rclcpp::Client<face_recognition::srv::FaceDetector>::SharedFuture result){
        auto response = result.get();
        //将返回的结果进行处理
    }
};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<FaceRecognitionClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}