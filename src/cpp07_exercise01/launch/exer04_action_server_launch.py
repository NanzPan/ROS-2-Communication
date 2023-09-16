from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 创建乌龟节点
    turtle = Node(package = "turtlesim",executable = "turtlesim_node")
    # 创建自定义节点
    server = Node(package = "cpp07_exercise01", executable = "exer04_action_server")

    return LaunchDescription([turtle,server])