/*
需求：创建参数客户端，查询并修改参数
步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
  3-1.创建参数客户端对象；
  3-2.连接服务端；
  3-3.查询参数；
  3-4.修改参数。
4.创建自定义节点类对象，并调用函数实现；
5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
// 3.定义节点类；
class ParamClient : public rclcpp::Node {
   public:
    ParamClient() : Node("paramclient_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "客户端建立！");
        // 3-1.创建参数客户端对象；
        // 参数一是当前对象依赖的节点，参数二是服务端节点名称。
        param_client = std::make_shared<rclcpp::SyncParametersClient>(
            this, "paramserver_node_cpp");
        /*
            问题：服务通信不是通过话题关联吗？为什么参数客户端是通过参数服务端的节点名称关联？
            答：
                1.参数服务端启动后，底层封装了多个服务通信的服务端；
                2.每个服务端都是采用/服务端节点名称/xxxxxx;
                3.参数客户端创建后，也会封装多个服务通信；
                4.这些客户端与服务端相呼应，也要使用相同的话题，因此客户端创建要使用服务端的节点名称。

         */
    }
    // 3-2.连接服务端；
    bool connect_server() {
        while (!param_client->wait_for_service(1s)) {
            RCLCPP_INFO(this->get_logger(), "服务连接中！！");
            if (!rclcpp::ok()) {
                RCLCPP_INFO(this->get_logger(), "连接失败！！");
                return false;
            }
        }
        return true;
    }
    // 3-3.查询参数；
    void get_param() {
        RCLCPP_INFO(this->get_logger(),
                    "--------------参数查询操作-----------------");
        // 获取单个参数；
        std::string car_name =
            param_client->get_parameter<std::string>("car_name");
        double height = param_client->get_parameter<double>("height");
        RCLCPP_INFO(this->get_logger(), "car_name = %s", car_name.c_str());
        RCLCPP_INFO(this->get_logger(), "height = %.2f /////", height);
        // 获取多个参数；
        auto param2 =
            param_client->get_parameters({"wheels", "car_name", "height"});
        for (auto &&param : param2) {
            RCLCPP_INFO(this->get_logger(), "%s = %s", param.get_name().c_str(),
                        param.value_to_string().c_str());
        }
        // 判断是否包含参数
        RCLCPP_INFO(this->get_logger(), "car_name?  %d",
                    param_client->has_parameter("car_name"));
        RCLCPP_INFO(this->get_logger(), "width?  %d",
                    param_client->has_parameter("width"));
    }

    // 3-4.修改参数.
    void update_param() {
        RCLCPP_INFO(this->get_logger(),
                    "--------------参数修改操作-----------------");
        param_client->set_parameters(
            {rclcpp::Parameter("car_name", "huawei"),
             rclcpp::Parameter("wheels", 6),
             // 设置参数服务端不存在的参数，注意：
             // rclcpp::NodeOptions().allow_undeclared_parameters(true)在服务端；
             rclcpp::Parameter("size", 6.0)});
        RCLCPP_INFO(this->get_logger(), "新设置的参数：%.2f",
                    param_client->get_parameter<double>("size"));
    }

   private:
    rclcpp::SyncParametersClient::SharedPtr param_client;
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc, argv);
    // 4.创建自定义节点类对象，并调用函数实现；
    auto client = std::make_shared<ParamClient>();
    bool flag = client->connect_server();
    if (!flag) {
        return 0;
    }
    client->get_param();
    client->update_param();
    client->get_param();

    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
