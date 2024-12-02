//
// Created by lining on 11/29/24.
//
#include "rclcpp/rclcpp.hpp"
#include <string>

using namespace std;

class PersonNode : public rclcpp::Node {
private:
    string name_;
    int age_;

public:
    PersonNode(const string &node_name,const string &name,const int &age):
    rclcpp::Node(node_name),name_(name),age_(age){

    }

    void eat(const string &food){
        RCLCPP_INFO(get_logger(),name_+" eat "+food);
    }

};


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PersonNode>("PersonNode","lining",38);
    RCLCPP_INFO(node->get_logger(), "PersonNode start");
    node->eat("apple");
    rclcpp::spin(node);
    rclcpp::shutdown();
    RCLCPP_INFO(node->get_logger(), "PersonNode end");
    return 0;
}