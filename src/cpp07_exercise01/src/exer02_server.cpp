/*
需求：发布目标点的坐标，接收并处理服务端反馈的结果。
步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
        3-1.创建乌龟姿态订阅方，回调函数中获取x坐标与y坐标；
        3-2.创建服务端；
        3-3.解析目标值，计算距离并反馈结果。
4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
// 1.包含头文件;
#include "base_interfaces_demo/srv/distance.hpp"
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlesim/srv/spawn.hpp"

using base_interfaces_demo::srv::Distance;
using std::placeholders::_1;
using std::placeholders::_2;

// 3.定义节点类；
class Exe02Server : public rclcpp::Node {
   public:
    Exe02Server() : Node("exe02_server_node_cpp"), x1(0.0), y1(0.0) {
        RCLCPP_INFO(this->get_logger(), "案例2服务端建立！");
        // 3-1.创建乌龟姿态订阅方，回调函数中获取x坐标与y坐标；
        t1_pose_sub = this->create_subscription<turtlesim::msg::Pose>(
            "/turtle1/pose", 10, std::bind(&Exe02Server::pose_cb, this, _1));
        // 3-2.创建服务端；
        // 两个占位符，一个是请求对象，一个响应对象
        server_ = this->create_service<Distance>(
            "distance_send",
            std::bind(&Exe02Server::distance_cb, this, _1, _2));
        // 3-3.解析目标值，计算距离并反馈结果.
    }

   private:
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr t1_pose_sub;
    rclcpp::Service<Distance>::SharedPtr server_;
    float x1, y1;
    void pose_cb(const turtlesim::msg::Pose::SharedPtr pose) {
        x1 = pose->x;
        y1 = pose->y;
    }
    void distance_cb(const Distance::Request::SharedPtr req,
                     Distance::Response::SharedPtr res) {
        // 解析x，y坐标
        float goal_x = req->x1;
        float goal_y = req->y1;
        // 计算距离
        float distance_x = goal_x - x1;
        float distance_y = goal_y - y1;
        float distance =
            std::sqrt(distance_x * distance_x + distance_y * distance_y);
        // 设置响应
        res->distance = distance;
        RCLCPP_INFO(this->get_logger(), "两只小龟的距离是 %.2f ",
                    res->distance);
    }
};

int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    rclcpp::spin(std::make_shared<Exe02Server>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
