cmake_minimum_required(VERSION 3.8)
project(manual_move_action)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(roarm_moveit REQUIRED)
find_package(roarm_moveit_cmd REQUIRED)    # <-- Added dependency on your cmd package
find_package(std_srvs REQUIRED)
find_package(rosidl_default_generators REQUIRED)


rosidl_generate_interfaces(${PROJECT_NAME}
  "action/MoveInfo.action"
)

ament_export_dependencies(rosidl_default_runtime)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp
)

add_executable(manual_move_client src/manual_move_client.cpp)
ament_target_dependencies(manual_move_client
  rclcpp
  rclcpp_action
  rclcpp_components
  roarm_moveit
  roarm_moveit_cmd             # <-- Added here to link with cmd package
)

add_executable(manual_move_server src/manual_move_server.cpp)
ament_target_dependencies(manual_move_server
  rclcpp
  rclcpp_action
  rclcpp_components
  roarm_moveit
  roarm_moveit_cmd             # <-- Added here as well
  std_srvs
)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(manual_move_client ${cpp_typesupport_target})
target_link_libraries(manual_move_server ${cpp_typesupport_target})

install(TARGETS
  manual_move_client
  manual_move_server
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

