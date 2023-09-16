from launch import LaunchDescription
from launch_ros.actions import Node

def genernate_launch_description():
    #1. 启动两个 turtlesim——node，其中一个要设置命名空间
    t1 = Node(package="turtlesim",executable="turtlesim_node")
    t2 = Node(package="turtlesim",executable="turtlesim_node",namespace="t2")

    # 2. 控制第二个乌龟调头



    # 3. 调用自定义节点，并且该节点调用顺序有要求，在2完成后
    return LaunchDescription([t1,t2])