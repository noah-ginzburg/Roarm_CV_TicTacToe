from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription, LogInfo
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    moveit_launch_path = os.path.join(
        get_package_share_directory('roarm_moveit_cmd'),
        'launch',
        'command_control.launch.py'
    )

    return LaunchDescription([
        # Debug print
        LogInfo(msg='Launching manual_move_script in new gnome-terminal window...'),

        # Launch manual_move C++ node in a new gnome-terminal
        ExecuteProcess(
            cmd=[
                'gnome-terminal', '--',
                'bash', '-c',
                'source /opt/ros/humble/setup.bash && source install/setup.bash && ros2 run 						manual_move_action manual_move_server;'
            ],
            shell=False
        ),
        
        # Launch manual_move C++ node in a new gnome-terminal
        ExecuteProcess(
            cmd=[
                'gnome-terminal', '--',
                'bash', '-c',
                'source /opt/ros/humble/setup.bash && source install/setup.bash && ros2 run 						manual_move_action manual_move_client;'
            ],
            shell=False
        ),

        # Launch the Python-based roarm_driver node
        Node(
            package='roarm_driver',
            executable='roarm_driver',
            name='roarm_driver_node',
            output='screen',
            emulate_tty=True
        ),
        
        Node(
            package='roarm_moveit_cmd',
            executable='movepointcmd',
            name='move_point_cmd_node',
            output='screen'
        ),
        
        Node(
            package='roarm_moveit_cmd',
            executable='setgrippercmd',
            name='gripper_action_client',
            output='screen'
        ),


        # Include the MoveIt launch file
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(moveit_launch_path)
        )
    ])

