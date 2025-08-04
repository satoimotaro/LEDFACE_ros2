from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config_file = os.path.join(
        get_package_share_directory('image_publisher'),
        'config',
        'image_pub_params.yaml'
    )

    return LaunchDescription([
        Node(
            package='image_publisher',
            executable='image_pub',
            name='image_publisher',
            parameters=[config_file]
        )
    ])
