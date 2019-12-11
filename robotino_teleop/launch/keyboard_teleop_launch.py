from launch import LaunchDescription
from launch import actions
from launch_ros.actions import Node

def generate_launch_description():

    ld = LaunchDescription([
        Node(
            package='robotino_teleop',
            node_namespace='',
            node_executable='keyboard_teleop_node',
            node_name='keyboard_teleop_node',
            output='screen',
            parameters=[
                {'scale_linear': 2.0},
                {'scale_angular': 2.0}]
        )
    ])

    ld.add_action(actions.SetLaunchConfiguration('emulate_tty', 'true'))

    return ld
