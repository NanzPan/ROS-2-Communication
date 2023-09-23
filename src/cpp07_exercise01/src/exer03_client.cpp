/*
需求：解析目标点坐标，解析结果并响应
步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
      3-1.创建客户端；
      3-2.连接服务；
      3-3.发送请求。
5.释放资源。
*/
// 1.包含头文件;
#include "base_interfaces_demo/srv/distance.hpp"
#include "rclcpp/rclcpp.hpp"

using base_interfaces_demo::srv::Distance;
using namespace ::std::chrono_literals;
// 3.定义节点类；
class Exe03Client : public rclcpp::Node {
   public:
    Exe03Client() : Node("exe03_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "案例2客户端建立！");
        client_ = this->create_client<Distance>("distance_send");
    }
    // 连接服务
    bool connect_server() {
        while (!client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
                             "强制终止客户端，连接失败！！");
                return false;
            }
            RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "正在玩命连接中！");
        }
        return true;
    }
    // 发送请求数据
    rclcpp::Client<Distance>::FutureAndRequestId send_goal(float x, float y,
                                                           float theta) {
        auto req = std::make_shared<Distance::Request>();
        req->x1 = x;
        req->y1 = y;
        req->theda = theta;
        return client_->async_send_request(req);
    }

   private:
    rclcpp::Client<Distance>::SharedPtr client_;
};
int main(int argc, char const *argv[]) {
    // 判断目标点坐标
    if (argc != 5) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                    "请提交x,y,theta三个参数！！");
        return 1;
    }
    // 接收提交参数
    float goal_x2 = atof(argv[1]);
    float goal_y2 = atof(argv[2]);
    float goal_theta2 = atof(argv[3]);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                "x : %.2f ,y : %.2f, theta : %.2f", goal_x2, goal_y2,
                goal_theta2);
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc, argv);
    // 创建客户端对象
    auto client = std::make_shared<Exe03Client>();
    // 确认连接
    bool flag = client->connect_server();
    if (!flag) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "连接失败！");
        return 0;
    }
    // 发送请求并处理响应
    auto res = client->send_goal(goal_x2, goal_y2, goal_theta2);
    // 处理
    if (rclcpp::spin_until_future_complete(client, res) ==
        rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(client->get_logger(), "两只乌龟距离是 %.2f ",
                    res.get()->distance);
    } else {
        RCLCPP_INFO(client->get_logger(), "请求错误！");
    }
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
