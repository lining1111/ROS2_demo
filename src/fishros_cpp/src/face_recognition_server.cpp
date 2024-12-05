//
// Created by lining on 12/4/24.
//

#include "rclcpp/rclcpp.hpp"
#include "face_recognition/srv/face_detector.hpp"
#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class FaceRecognitionServer : public rclcpp::Node {
private:
    rclcpp::Service<face_recognition::srv::FaceDetector>::SharedPtr _server;
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
    FaceRecognitionServer() : rclcpp::Node("FaceRecognitionServer") {
        RCLCPP_INFO(get_logger(), "FaceRecognitionServer start");
        _server = create_service<face_recognition::srv::FaceDetector>("face_recognition_srv",
                                                                      std::bind(&FaceRecognitionServer::handle, this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2));

    };


};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = make_shared<FaceRecognitionServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}