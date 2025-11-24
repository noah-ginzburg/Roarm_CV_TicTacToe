#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "manual_move_action/action/move_info.hpp"
 // Replace with your action path if needed
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using namespace std::chrono_literals;

class MinimalActionClient : public rclcpp::Node
{
public:
  using MoveInfo = manual_move_action::action::MoveInfo;
  using GoalHandleMoveInfo = rclcpp_action::ClientGoalHandle<MoveInfo>;

  MinimalActionClient() : Node("minimal_action_client")
  {
    // Create the action client for "MoveInfo"
    action_client_ = rclcpp_action::create_client<MoveInfo>(this, "MoveInfo");

    // Wait until the action server is available
    while (!action_client_->wait_for_action_server(1s))
    {
      RCLCPP_INFO(this->get_logger(), "Waiting for action server...");
    }
  }

  void send_goal()
  {
    // Random data
    auto goal_msg = MoveInfo::Goal();
    goal_msg.x = 0.2;
    goal_msg.y = 0.0;
    goal_msg.z = 0.0;
    goal_msg.t = 0.6; 

    RCLCPP_INFO(this->get_logger(), "Sending goal...");

    rclcpp_action::Client<MoveInfo>::SendGoalOptions options;
    options.feedback_callback =
        std::bind(&MinimalActionClient::feedback_callback, this,
                  std::placeholders::_1, std::placeholders::_2);
    options.result_callback = std::bind(&MinimalActionClient::result_callback,
                                        this, std::placeholders::_1);

    action_client_->async_send_goal(goal_msg, options);
  }

private:
  rclcpp_action::Client<MoveInfo>::SharedPtr action_client_;

  // Movement feedback is provided via move_it's service which handles the kinematics and actual arm motion
  void feedback_callback(GoalHandleMoveInfo::SharedPtr,
                    const std::shared_ptr<const MoveInfo::Feedback> feedback)
  {
    // Handle feedback
    RCLCPP_INFO(this->get_logger(), "Feedback received (not yet handled)");
  }

  void result_callback(const GoalHandleMoveInfo::WrappedResult &result)
  {
    // Handle result
    switch (result.code)
    {
    case rclcpp_action::ResultCode::SUCCEEDED:
      RCLCPP_INFO(this->get_logger(), "Goal succeeded: %s",
                  result.result->message.c_str());
      break;
    case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_WARN(this->get_logger(), "Goal aborted");
      break;
    case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_WARN(this->get_logger(), "Goal canceled");
      break;
    default:
      RCLCPP_ERROR(this->get_logger(), "Unknown result code");
      break;
    }
  }
};

//Helper function
void PromptUser(const std::shared_ptr<MinimalActionClient>& node)
{
  while (rclcpp::ok())
  {
    std::cout << "Press ENTER to send a goal..." << std::endl;
    std::cin.get();
    node->send_goal();  
  }
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MinimalActionClient>();

  std::thread spin_thread([&]() {
    rclcpp::spin(node);
  });

  PromptUser(node);

  spin_thread.join();
  rclcpp::shutdown();
  return 0;
}

