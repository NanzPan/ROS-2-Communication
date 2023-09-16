from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess,RegisterEventHandler
from launch.event_handlers import OnProcessExit


def generate_launch_description():
    #1. 启动两个 turtlesim——node，其中一个要设置命名空间
    t1 = Node(package="turtlesim",executable="turtlesim_node")
    t2 = Node(package="turtlesim",executable="turtlesim_node",namespace="t2")

    # 2. 控制第二个乌龟调头
    rotate = ExecuteProcess(
        #cmd:传参是一个列表，里面有储存终端指令，直接通过他去控制终端发布指令
        cmd=["ros2 action send_goal /t2/turtle1/rotate_absolute turtlesim/action/RotateAbsolute \"{'theta': 3.14}\""],
        #output:指日志输出在哪,both就是输出到日志有输出到cmd终端
        output="both",
        #shell:布尔值，是否当做终端指令来执行
        shell = True
    )

    # 3. 调用自定义节点，并且该节点调用顺序有要求，在2完成后才
    exer01 = Node(package="cpp07_exercise01",executable="exer01_pub_sub")
    # 4. 怎么控制节点运行顺序？通过注册事件完成；
    # 创建事件注册对象，在对象中声明针对哪个目标节点，在哪个事件触发时，执行哪种操作？
    register_rotate_exit_event = RegisterEventHandler(
        # 创建一个新对象
        event_handler=OnProcessExit( #触发动作
            # 目标节点
            target_action=rotate,
            # 触发执行的事件
            on_exit=exer01
        )
    )

    return LaunchDescription([t1,t2,rotate,register_rotate_exit_event])