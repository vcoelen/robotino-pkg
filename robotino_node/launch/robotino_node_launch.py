from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    hostname = LaunchConfiguration('hostname')

    return LaunchDescription([
        DeclareLaunchArgument(
            'hostname',
            default_value='172.26.1.1',
            description='Hostname of the robotino'),

        Node(
            package='robotino_node',
            node_namespace='',
            node_executable='robotino_node',
            node_name='robotino_node',
            output='screen',
            remappings=[
                ('robotino_joint_states', 'joint_states')],
            parameters=[{'hostname': hostname},
                {'max_linear_vel': 0.5},
                {'min_linear_vel': 0.05},
                {'max_angular_vel': 3.0},
                {'min_angular_vel': 0.1},
                {'downsample_kinect': True},
                {'leaf_size_kinect': 0.04}],
        ),
        Node(
            package='robotino_node',
            node_namespace='',
            node_executable='robotino_odometry_node',
            node_name='robotino_odometry_node',
            parameters=[{'hostname': hostname}]
        )
    ])
