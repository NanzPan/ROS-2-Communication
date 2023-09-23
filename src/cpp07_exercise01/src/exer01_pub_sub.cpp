/*
需求：订阅订阅乌龟一的位姿，线速度和角速度，生成并发布控制t2的指令
明确：
订阅话题；/turtle1/pose
订阅消息；turtlesim/msg/Pose  (Type)类型

          "x: 0.0
          y: 0.0
          theta: 0.0              (格式)
          linear_velocity: 0.0
          angular_velocity: 0.0
"# ros2 interfaces proto /turtlesim/msg/Pose

发布话题：/t2/turtle1/cmd_vel
发布消息；geometry_msgs/msg/Twist  (Type)
"linear:
  x: 0.0 ----(前后)
  y: 0.0 ----（左右）
  z: 0.0 ----（上下）
angular:
  x: 0.0 ----（roll）翻转
  y: 0.0 ----（pitch）俯仰
  z: 0.0 ----（偏航yaw）
"


步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
    3-1 创建发布方
    3-2 创建订阅方（订阅Pose，解析速度）
    3-3 订阅方回调函数处理速度生成并发布乌龟2的速度指令
4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
// 1.包含头文件;
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"

// 3.定义节点类；
class Exer01PubSub : public rclcpp::Node {
   public:
    Exer01PubSub() : Node("exer01_pub_sub_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "案例1建立！");
        // 3-1 创建发布方
        pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/t2/turtle1/cmd_vel", 10);
        // 3-2 创建订阅方（订阅Pose，解析速度）
        sub_ = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose ", 10,
            std::bind(&Exer01PubSub::sub_cb, this, std::placeholders::_1));
    }

   private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
    void sub_cb(const turtlesim::msg::Pose &pose) {
        // 3-3 订阅方回调函数处理速度生成并发布乌龟2的速度指令
        // 创建新速度指令并发布
        // 创建一个名为 twist 的变量
        geometry_msgs::msg::Twist twist;
        twist.linear.x = pose.linear_velocity;
        twist.angular.z = -pose.angular_velocity;
        // 发布
        pub_->publish(twist);
    }
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    rclcpp::spin(std::make_shared<Exer01PubSub>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
