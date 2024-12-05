//
// Created by lining on 12/5/24.
//
#include "fishros_cpp/robot.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"
#include <chrono>


using namespace std;

class ActionRobot : public rclcpp::Node {
public:
    using MoveRobot = robot_control_interfaces::action::MoveRobot;
    ActionRobot(const string &name) : rclcpp::Node(name) {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());

        action_server_ = rclcpp_action::create_server<MoveRobot>(this,"move_robot",
                                                          std::bind(&ActionRobot::handle_goal,this,std::placeholders::_1,std::placeholders::_2),
                                                          std::bind(&ActionRobot::handle_cancel,this,std::placeholders::_1),
                                                          std::bind(&ActionRobot::handle_accepted,this,std::placeholders::_1)
                                                          );
    }
private:
    Robot robot;
    rclcpp_action::Server<MoveRobot>::SharedPtr action_server_;
    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID &uuid, shared_ptr<const MoveRobot::Goal> goal){
        RCLCPP_INFO(this->get_logger(), "Received goal request with distance %f",
                    goal->distance);
        (void)uuid;
        if (fabs(goal->distance > 100)) {
            RCLCPP_WARN(this->get_logger(), "目标距离太远了，本机器人表示拒绝！");
            return rclcpp_action::GoalResponse::REJECT;
        }
        RCLCPP_INFO(this->get_logger(),
                    "目标距离%f我可以走到，本机器人接受，准备出发！",
                    goal->distance);
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(
            const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobot>> goal_handle) {
        RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
        (void)goal_handle;
        robot.stop_move(); /*认可取消执行，让机器人停下来*/
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void execute_move(const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobot>> goal_handle) {
        const auto goal = goal_handle->get_goal();
        RCLCPP_INFO(this->get_logger(), "开始执行移动 %f 。。。", goal->distance);

        auto result = std::make_shared<MoveRobot::Result>();
        rclcpp::Rate rate(2);
        robot.set_goal(goal->distance);
        while (rclcpp::ok() && !robot.close_goal()) {
            robot.move_step();
            auto feedback = std::make_shared<MoveRobot::Feedback>();
            feedback->pose = robot.get_current_pose();
            feedback->status = robot.get_status();
            goal_handle->publish_feedback(feedback);
            /*检测任务是否被取消*/
            if (goal_handle->is_canceling()) {
                result->pose = robot.get_current_pose();
                goal_handle->canceled(result);
                RCLCPP_INFO(this->get_logger(), "Goal Canceled");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Publish Feedback"); /*Publish feedback*/
            rate.sleep();
        }

        result->pose = robot.get_current_pose();
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal Succeeded");
    }

    void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobot>> goal_handle) {
        using std::placeholders::_1;
        std::thread{std::bind(&ActionRobot::execute_move, this, _1), goal_handle}
                .detach();
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ActionRobot>("action_robot");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}