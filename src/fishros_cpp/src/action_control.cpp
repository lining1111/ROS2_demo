//
// Created by lining on 12/5/24.
//
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"

using namespace std;
using namespace std::chrono_literals;

class ActionControl : public rclcpp::Node {
public:
    using MoveRobot = robot_control_interfaces::action::MoveRobot;

    ActionControl(const string &name, const rclcpp::NodeOptions &node_options = rclcpp::NodeOptions())
            : rclcpp::Node(name, node_options) {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
        client_ptr_ = rclcpp_action::create_client<MoveRobot>(this, "move_robot");
        timer_ = create_wall_timer(500ms, bind(&ActionControl::send_goal,this));

    }

    void send_goal() {
        this->timer_->cancel();

        if (!this->client_ptr_->wait_for_action_server(10s)) {
            RCLCPP_ERROR(this->get_logger(),
                         "Action server not available after waiting");
            rclcpp::shutdown();
            return;
        }

        auto goal_msg = MoveRobot::Goal();
        goal_msg.distance = 10;

        RCLCPP_INFO(this->get_logger(), "Sending goal");

        auto send_goal_options =
                rclcpp_action::Client<MoveRobot>::SendGoalOptions();
        send_goal_options.goal_response_callback =
                std::bind(&ActionControl::goal_response_callback, this, placeholders::_1);
        send_goal_options.feedback_callback =
                std::bind(&ActionControl::feedback_callback, this, placeholders::_1, placeholders::_2);
        send_goal_options.result_callback =
                std::bind(&ActionControl::result_callback, this, placeholders::_1);
        this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
    }

private:
    rclcpp_action::Client<MoveRobot>::SharedPtr client_ptr_;
    rclcpp::TimerBase::SharedPtr timer_;

    void goal_response_callback(shared_future<rclcpp_action::ClientGoalHandle<MoveRobot>::SharedPtr> future) {
        auto goal_handle = future.get();
        if (!goal_handle) {
            RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
        } else {
            RCLCPP_INFO(this->get_logger(),
                        "Goal accepted by server, waiting for result");
        }
    }

    void feedback_callback(
            rclcpp_action::ClientGoalHandle<MoveRobot>::SharedPtr,
            const std::shared_ptr<const MoveRobot::Feedback> feedback) {
        RCLCPP_INFO(this->get_logger(), "Feedback current pose:%f", feedback->pose);
    }

    void result_callback(const rclcpp_action::ClientGoalHandle<MoveRobot>::WrappedResult &result) {
        switch (result.code) {
            case rclcpp_action::ResultCode::SUCCEEDED:
                break;
            case rclcpp_action::ResultCode::ABORTED:
                RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
                return;
            case rclcpp_action::ResultCode::CANCELED:
                RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
                return;
            default:
                RCLCPP_ERROR(this->get_logger(), "Unknown result code");
                return;
        }

        RCLCPP_INFO(this->get_logger(), "Result received: %f", result.result->pose);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ActionControl>("action_control");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}