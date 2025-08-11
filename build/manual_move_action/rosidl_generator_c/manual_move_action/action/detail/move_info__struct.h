// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from manual_move_action:action/MoveInfo.idl
// generated code does not contain a copyright notice

#ifndef MANUAL_MOVE_ACTION__ACTION__DETAIL__MOVE_INFO__STRUCT_H_
#define MANUAL_MOVE_ACTION__ACTION__DETAIL__MOVE_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_Goal
{
  double x;
  double y;
  double z;
  /// t = gripper target position
  double t;
} manual_move_action__action__MoveInfo_Goal;

// Struct for a sequence of manual_move_action__action__MoveInfo_Goal.
typedef struct manual_move_action__action__MoveInfo_Goal__Sequence
{
  manual_move_action__action__MoveInfo_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_Result
{
  bool success;
  rosidl_runtime_c__String message;
} manual_move_action__action__MoveInfo_Result;

// Struct for a sequence of manual_move_action__action__MoveInfo_Result.
typedef struct manual_move_action__action__MoveInfo_Result__Sequence
{
  manual_move_action__action__MoveInfo_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_Feedback
{
  double progress;
} manual_move_action__action__MoveInfo_Feedback;

// Struct for a sequence of manual_move_action__action__MoveInfo_Feedback.
typedef struct manual_move_action__action__MoveInfo_Feedback__Sequence
{
  manual_move_action__action__MoveInfo_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "manual_move_action/action/detail/move_info__struct.h"

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  manual_move_action__action__MoveInfo_Goal goal;
} manual_move_action__action__MoveInfo_SendGoal_Request;

// Struct for a sequence of manual_move_action__action__MoveInfo_SendGoal_Request.
typedef struct manual_move_action__action__MoveInfo_SendGoal_Request__Sequence
{
  manual_move_action__action__MoveInfo_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} manual_move_action__action__MoveInfo_SendGoal_Response;

// Struct for a sequence of manual_move_action__action__MoveInfo_SendGoal_Response.
typedef struct manual_move_action__action__MoveInfo_SendGoal_Response__Sequence
{
  manual_move_action__action__MoveInfo_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} manual_move_action__action__MoveInfo_GetResult_Request;

// Struct for a sequence of manual_move_action__action__MoveInfo_GetResult_Request.
typedef struct manual_move_action__action__MoveInfo_GetResult_Request__Sequence
{
  manual_move_action__action__MoveInfo_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "manual_move_action/action/detail/move_info__struct.h"

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_GetResult_Response
{
  int8_t status;
  manual_move_action__action__MoveInfo_Result result;
} manual_move_action__action__MoveInfo_GetResult_Response;

// Struct for a sequence of manual_move_action__action__MoveInfo_GetResult_Response.
typedef struct manual_move_action__action__MoveInfo_GetResult_Response__Sequence
{
  manual_move_action__action__MoveInfo_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "manual_move_action/action/detail/move_info__struct.h"

/// Struct defined in action/MoveInfo in the package manual_move_action.
typedef struct manual_move_action__action__MoveInfo_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  manual_move_action__action__MoveInfo_Feedback feedback;
} manual_move_action__action__MoveInfo_FeedbackMessage;

// Struct for a sequence of manual_move_action__action__MoveInfo_FeedbackMessage.
typedef struct manual_move_action__action__MoveInfo_FeedbackMessage__Sequence
{
  manual_move_action__action__MoveInfo_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} manual_move_action__action__MoveInfo_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MANUAL_MOVE_ACTION__ACTION__DETAIL__MOVE_INFO__STRUCT_H_
