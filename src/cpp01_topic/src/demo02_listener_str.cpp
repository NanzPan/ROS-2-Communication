/*
    需求：订阅发布方发布的消息，并输出到终端。
    步骤：
        1.包含头文件；
        2.初始化 ROS2 客户端；
        3.定义节点类；
            3-1.创建订阅方；
            3-2.处理订阅到的消息。
        4.调用spin函数，并传入节点对象指针；
        5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
// 3.定义节点类；
class listener : public rclcpp::Node {
   public:
    listener() : Node("lister_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "订阅方创建！:");
        // 3-1.创建订阅方；
        /*
            模版：消息类型；
            参数：
                1.话题名称；
                2.Qos，（队列长度）；
                3.回调函数；
            返回值：订阅对象指针；
         */
        subscription_ = this->create_subscription<std_msgs::msg::String>("chatter", 10,std::bind(&listener::do_cb, this, std::placeholders::_1));
    }

   private:
    void do_cb(const std_msgs::msg::String &msg1) {
        // 3-2.处理订阅到的消息.
        RCLCPP_INFO(this->get_logger(), "订阅到的消息是：%s", msg1.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    rclcpp::spin(std::make_shared<listener>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
