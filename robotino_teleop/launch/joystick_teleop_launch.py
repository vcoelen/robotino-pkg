from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([
        # Joy Node
        Node(
            package='joy',
            node_namespace='',
            node_executable='joy_node',
            node_name='joy',
            parameters=[
                {'dev': '/dev/input/js0'},
                {'deadzone': 0.1}]
        ),
        # Joystick Teleop Node
        Node(
            package='robotino_teleop',
            node_namespace='',
            node_executable='joystick_teleop_node',
            node_name='joystick_teleop_node',
            output='screen',
            parameters=[
                # Axes
                {'axis_linear_x': 1},
                {'axis_linear_y': 0},
                {'axis_angular': 2},

                # Scale
                {'scale_linear': 0.5},
                {'scale_angular': 1.0}]
        )
    ])
