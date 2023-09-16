from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
    x = 6
    y = 9
    theta = 3.14
    name = "t2"
    # 生成一只新乌龟，
    #ros2 service call /spawn turtlesim/srv/Spawn "{'x': 6.0,'y': 9.0,'theta': 3.14}"
    spawn = ExecuteProcess(
        cmd = ["ros2 service call /spawn turtlesim/srv/Spawn \"{'x': " + str(x) + ",'y': " + str(y) + ",'theta': " + str(theta) + ",'name': '" + name+ "'}\""],
# 在你的代码中，`'name': '" + name + "'"` 中的单引号用于将 `name` 变量的值作为字符串插入到JSON消息中。这是因为JSON消息的属性通常都包含在单引号或双引号中，所以为了确保 `name` 的值在JSON消息中被正确解释为字符串，你需要将其用引号括起来。
# 如果你使用 `"name": " + name + "`，则 `name` 的值将直接插入到JSON消息中，而不会被视为字符串。这可能导致JSON消息的格式不正确，特别是如果 `name` 的值包含空格或特殊字符时。因此，为了确保正确的JSON格式，你应该将字符串值用引号括起来，就像你的代码中所做的那样。

        output = "both",
        shell = True
    )
    client = Node(package="cpp07_exercise01",executable="exer03_client",
            arguments = [str(x),str(y),str(theta)])   #三个参数
            # ros2 run cpp07_exercise01 exer03_client 6 9 0.0 --ros-args    ///四个参数
            #传到程序里面就变成5个了
    return LaunchDescription([spawn,client])
    # 调用客户端发送坐标