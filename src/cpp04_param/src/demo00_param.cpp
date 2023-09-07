/*
需求：订阅发布方发布的消息，并输出到终端。
步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
3-1.参数对象创建
3-2.参数对象解析（获取键，值，将获取的值转换成字符串等..）
4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"

// 3.定义节点类；
class MyParam : public rclcpp::Node {
   public:
    MyParam() : Node("my_param_node_cpp") {
        RCLCPP_INFO(this->get_logger(),"参数API使用");
        // 3-1.参数对象创建
        rclcpp::Parameter p1("car_name", "nio");
        rclcpp::Parameter p2("height", 1.65);
        rclcpp::Parameter p3("wheels", 4);
        // 3-2.参数对象解析（获取键，值，将获取的值转换成字符串等..)
        //解析值
        RCLCPP_INFO(this->get_logger(), "car_name = %s",p1.as_string().c_str());
        RCLCPP_INFO(this->get_logger(), "height = %.2f",p2.as_double());
        RCLCPP_INFO(this->get_logger(), "wheels = %ld",p3.as_int());
        //这里写%ld是因为as_int 是int64类型的，属于长整型；

        //获取参数的键(get_name)
        RCLCPP_INFO(this->get_logger(), "name = %s",p1.get_name().c_str());
        RCLCPP_INFO(this->get_logger(), "type = %s",p1.get_type_name().c_str());
        RCLCPP_INFO(this->get_logger(), "valuetostring = %s",p2.value_to_string().c_str());
        
        
    }
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    rclcpp::spin(std::make_shared<MyParam>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
