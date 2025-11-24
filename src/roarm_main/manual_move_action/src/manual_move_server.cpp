#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

#include "manual_move_action/action/move_info.hpp"
#include "roarm_moveit/srv/move_point_cmd.hpp"

#include <std_srvs/srv/empty.hpp>
#include "std_msgs/msg/float32.hpp"


using namespace std::chrono_literals;

namespace manual_move_action // <-- Replace with your desired namespace
{

const double NO_T = -1;

class MinimalActionServer : public rclcpp::Node
{
public:
  using CustomAction = manual_move_action::action::MoveInfo; // <-- Replace
  using GoalHandle = rclcpp_action::ServerGoalHandle<CustomAction>;

  explicit MinimalActionServer(
      const rclcpp::NodeOptions &options = rclcpp::NodeOptions())
      : Node("minimal_action_server", options)
  {
    using namespace std::placeholders;

    action_server_ = rclcpp_action::create_server<CustomAction>(
        this,
        "MoveInfo", // <-- This is the action name clients use to connect
        std::bind(&MinimalActionServer::handle_goal, this, _1, _2),
        std::bind(&MinimalActionServer::handle_cancel, this, _1),
        std::bind(&MinimalActionServer::handle_accepted, this, _1));

    stop_client_ =
        this->create_client<std_srvs::srv::Empty>("/move_group/stop");
    move_point_client =
        this->create_client<roarm_moveit::srv::MovePointCmd>("move_point_cmd");
    gripper_cmd_pub_ = this->create_publisher<std_msgs::msg::Float32>("/gripper_cmd", 10);

  }

private:
  rclcpp_action::Server<CustomAction>::SharedPtr action_server_;
  rclcpp::Client<roarm_moveit::srv::MovePointCmd>::SharedPtr move_point_client;
  rclcpp::Client<std_srvs::srv::Empty>::SharedPtr stop_client_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr gripper_cmd_pub_;

  double xI, xC, xF;
  double yI, yC, yF;
  double zI, zC, zF;
  double tI, tF;

  bool executing_goal_ = false;
  std::atomic<bool> should_stop_;

  std::queue<std::shared_ptr<GoalHandle>> goal_queue_;
  std::mutex queue_mutex_;

  rclcpp_action::GoalResponse
  handle_goal(const rclcpp_action::GoalUUID &,
              std::shared_ptr<const CustomAction::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received goal request");

    return rclcpp_action::GoalResponse::ACCEPT_AND_DEFER;
  }

  rclcpp_action::CancelResponse
  handle_cancel(const std::shared_ptr<GoalHandle> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Received cancel request");

    should_stop_ = true;

    while (!goal_queue_.empty())
    {
      goal_queue_.pop();
    }

    if (stop_client_->wait_for_service(1s))
    {
      auto stop_request = std::make_shared<std_srvs::srv::Empty::Request>();
      stop_client_->async_send_request(stop_request);
      RCLCPP_INFO(this->get_logger(), "Sent stop request to MoveIt");
    }
    else
    {
      RCLCPP_WARN(this->get_logger(), "MoveIt stop service not available");
    }

    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handle_accepted(const std::shared_ptr<GoalHandle> goal_handle)
  {
    std::lock_guard<std::mutex> lock(queue_mutex_); // Lock mutex
    goal_queue_.push(goal_handle);
    RCLCPP_INFO(this->get_logger(), "Pushed goal request");

    if (!executing_goal_)
    {
      executing_goal_ = true;
      // Start processing the first goal in a new thread:
      std::thread(&MinimalActionServer::process_queue, this).detach();
    }
  }

  void process_queue()
  {
    while (true)
    {
      std::shared_ptr<GoalHandle> current_goal;

      {
        std::lock_guard<std::mutex> lock(queue_mutex_);

        if (goal_queue_.empty())
        {
          executing_goal_ = false; // no more goals to process
          return;
        }
        current_goal = goal_queue_.front();
        goal_queue_.pop();
      }

      execute(current_goal);
    }
  }

  void execute(const std::shared_ptr<GoalHandle> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal...");
    rclcpp::Rate rate(10); // 10 Hz loop rate
    should_stop_ = false;

    auto result =
        std::make_shared<manual_move_action::action::MoveInfo::Result>();
    auto goal = goal_handle->get_goal();

    rclcpp::Client<roarm_moveit::srv::MovePointCmd>::SharedFuture moveResponse;

    goal_handle->execute();

    if (goal->t != NO_T)
    {
      RCLCPP_INFO(this->get_logger(), "entered if statment");
      auto msg = std_msgs::msg::Float32();
      msg.data = goal->t; 
      RCLCPP_INFO(this->get_logger(), "pubishing to gripper");
      gripper_cmd_pub_->publish(msg);
      RCLCPP_INFO(this->get_logger(), "published to gripper");
      

    }

    if (goal->x != -1.0)
    {
      RCLCPP_INFO(this->get_logger(), "setting goal coords");
      xI = goal->x;
      yI = goal->y;
      zI = goal->z;

      auto moveReq =
          std::make_shared<roarm_moveit::srv::MovePointCmd::Request>();
      moveReq->x = xI;
      moveReq->y = yI;
      moveReq->z = zI;
    
      RCLCPP_INFO(this->get_logger(), "no torqque, Sending move req");
      auto future_and_request = move_point_client->async_send_request(moveReq);
      moveResponse = future_and_request.future.share();
    }
    
    while (rclcpp::ok())
    {
      if (should_stop_)
      {
        result->success = false;
        result->message = "Movement was Cancelled";

        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal and movement canceled");
        return;
      }

      // Optionally add feedback here

      if (moveResponse.valid() && moveResponse.wait_for(std::chrono::seconds(
                                      0)) == std::future_status::ready)
      {
        auto response = moveResponse.get();

        if (response->success)
        {
          result->success = true;
          result->message = "Reached target position successfully";

          goal_handle->succeed(result);
          RCLCPP_INFO(this->get_logger(), "Goal succeeded");
          return;
        }
        else
        {
          result->success = false;
          result->message = "Movement failed";

          goal_handle->abort(result);
          RCLCPP_WARN(this->get_logger(), "Goal aborted");
          return;
        }
      }

      rate.sleep();
    }
  }
};

} // namespace manual_move_action

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<manual_move_action::MinimalActionServer>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}