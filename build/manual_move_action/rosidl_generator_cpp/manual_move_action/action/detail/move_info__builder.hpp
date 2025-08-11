// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from manual_move_action:action/MoveInfo.idl
// generated code does not contain a copyright notice

#ifndef MANUAL_MOVE_ACTION__ACTION__DETAIL__MOVE_INFO__BUILDER_HPP_
#define MANUAL_MOVE_ACTION__ACTION__DETAIL__MOVE_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "manual_move_action/action/detail/move_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_Goal_t
{
public:
  explicit Init_MoveInfo_Goal_t(::manual_move_action::action::MoveInfo_Goal & msg)
  : msg_(msg)
  {}
  ::manual_move_action::action::MoveInfo_Goal t(::manual_move_action::action::MoveInfo_Goal::_t_type arg)
  {
    msg_.t = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Goal msg_;
};

class Init_MoveInfo_Goal_z
{
public:
  explicit Init_MoveInfo_Goal_z(::manual_move_action::action::MoveInfo_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveInfo_Goal_t z(::manual_move_action::action::MoveInfo_Goal::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_MoveInfo_Goal_t(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Goal msg_;
};

class Init_MoveInfo_Goal_y
{
public:
  explicit Init_MoveInfo_Goal_y(::manual_move_action::action::MoveInfo_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveInfo_Goal_z y(::manual_move_action::action::MoveInfo_Goal::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_MoveInfo_Goal_z(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Goal msg_;
};

class Init_MoveInfo_Goal_x
{
public:
  Init_MoveInfo_Goal_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveInfo_Goal_y x(::manual_move_action::action::MoveInfo_Goal::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_MoveInfo_Goal_y(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_Goal>()
{
  return manual_move_action::action::builder::Init_MoveInfo_Goal_x();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_Result_message
{
public:
  explicit Init_MoveInfo_Result_message(::manual_move_action::action::MoveInfo_Result & msg)
  : msg_(msg)
  {}
  ::manual_move_action::action::MoveInfo_Result message(::manual_move_action::action::MoveInfo_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Result msg_;
};

class Init_MoveInfo_Result_success
{
public:
  Init_MoveInfo_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveInfo_Result_message success(::manual_move_action::action::MoveInfo_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveInfo_Result_message(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_Result>()
{
  return manual_move_action::action::builder::Init_MoveInfo_Result_success();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_Feedback_progress
{
public:
  Init_MoveInfo_Feedback_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::manual_move_action::action::MoveInfo_Feedback progress(::manual_move_action::action::MoveInfo_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_Feedback>()
{
  return manual_move_action::action::builder::Init_MoveInfo_Feedback_progress();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_SendGoal_Request_goal
{
public:
  explicit Init_MoveInfo_SendGoal_Request_goal(::manual_move_action::action::MoveInfo_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::manual_move_action::action::MoveInfo_SendGoal_Request goal(::manual_move_action::action::MoveInfo_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_SendGoal_Request msg_;
};

class Init_MoveInfo_SendGoal_Request_goal_id
{
public:
  Init_MoveInfo_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveInfo_SendGoal_Request_goal goal_id(::manual_move_action::action::MoveInfo_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveInfo_SendGoal_Request_goal(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_SendGoal_Request>()
{
  return manual_move_action::action::builder::Init_MoveInfo_SendGoal_Request_goal_id();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_SendGoal_Response_stamp
{
public:
  explicit Init_MoveInfo_SendGoal_Response_stamp(::manual_move_action::action::MoveInfo_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::manual_move_action::action::MoveInfo_SendGoal_Response stamp(::manual_move_action::action::MoveInfo_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_SendGoal_Response msg_;
};

class Init_MoveInfo_SendGoal_Response_accepted
{
public:
  Init_MoveInfo_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveInfo_SendGoal_Response_stamp accepted(::manual_move_action::action::MoveInfo_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MoveInfo_SendGoal_Response_stamp(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_SendGoal_Response>()
{
  return manual_move_action::action::builder::Init_MoveInfo_SendGoal_Response_accepted();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_GetResult_Request_goal_id
{
public:
  Init_MoveInfo_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::manual_move_action::action::MoveInfo_GetResult_Request goal_id(::manual_move_action::action::MoveInfo_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_GetResult_Request>()
{
  return manual_move_action::action::builder::Init_MoveInfo_GetResult_Request_goal_id();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_GetResult_Response_result
{
public:
  explicit Init_MoveInfo_GetResult_Response_result(::manual_move_action::action::MoveInfo_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::manual_move_action::action::MoveInfo_GetResult_Response result(::manual_move_action::action::MoveInfo_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_GetResult_Response msg_;
};

class Init_MoveInfo_GetResult_Response_status
{
public:
  Init_MoveInfo_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveInfo_GetResult_Response_result status(::manual_move_action::action::MoveInfo_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MoveInfo_GetResult_Response_result(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_GetResult_Response>()
{
  return manual_move_action::action::builder::Init_MoveInfo_GetResult_Response_status();
}

}  // namespace manual_move_action


namespace manual_move_action
{

namespace action
{

namespace builder
{

class Init_MoveInfo_FeedbackMessage_feedback
{
public:
  explicit Init_MoveInfo_FeedbackMessage_feedback(::manual_move_action::action::MoveInfo_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::manual_move_action::action::MoveInfo_FeedbackMessage feedback(::manual_move_action::action::MoveInfo_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_FeedbackMessage msg_;
};

class Init_MoveInfo_FeedbackMessage_goal_id
{
public:
  Init_MoveInfo_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveInfo_FeedbackMessage_feedback goal_id(::manual_move_action::action::MoveInfo_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveInfo_FeedbackMessage_feedback(msg_);
  }

private:
  ::manual_move_action::action::MoveInfo_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::manual_move_action::action::MoveInfo_FeedbackMessage>()
{
  return manual_move_action::action::builder::Init_MoveInfo_FeedbackMessage_goal_id();
}

}  // namespace manual_move_action

#endif  // MANUAL_MOVE_ACTION__ACTION__DETAIL__MOVE_INFO__BUILDER_HPP_
