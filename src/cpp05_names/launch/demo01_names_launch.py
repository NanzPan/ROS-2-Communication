
#launch必需
from launch import LaunchDescription
from launch_ros.actions import Node
#函数名称固定
def generate_launch_description():
    
    return LaunchDescription([
        #传参，传入的就是一个列表
        #列表是被启动节点的列表，通过Node来创建
        Node(package="turtlesim",executable="turtlesim_node",name="t1")

    ])