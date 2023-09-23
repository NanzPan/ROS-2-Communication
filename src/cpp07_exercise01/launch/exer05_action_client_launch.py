from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
    #目标点坐标
    x = 0.54
    y = 0.54
    theta = 0.0
    name = "t3"
    # 生成新的乌龟、
    spawn = ExecuteProcess(
        cmd = ["ros2 service call /spawn turtlesim/srv/Spawn \"{'x': "+ str(x)+", 'y': "+str(y)+", 'theta': "+str(theta)+",'name': '"+name+"'}\""],
        output = "both",
        shell = True
    )
    client = Node(package="cpp07_exercise01",executable="exer05_action_client",
            arguments=[str(x),str(y),str(theta)])
    return LaunchDescription([spawn,client])