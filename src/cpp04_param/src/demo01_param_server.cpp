/*
需求：创建参数服务端并操作参数
步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
  3-1.增；
  3-2.查；
  3-3.改；
  3-4.删；
4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"

// 3.定义节点类；
class ParamServer : public rclcpp::Node {
   public:
    // 如果允许删除参数，要通过 NodeOptions 声明；
    ParamServer()
        : Node("paramserver_node_cpp",
               rclcpp::NodeOptions().allow_undeclared_parameters(true)) {
        RCLCPP_INFO(this->get_logger(), "服务端建立！");
    }
    // 3-1.增；
    void declare_param() {
        RCLCPP_INFO(this->get_logger(),
                    "------------------------增-----------------------");
        this->declare_parameter("car_name", "nio");
        this->declare_parameter("height", 1.55);
        this->declare_parameter("wheels", 5);
        // 也可以用这个来设置，但必须保证
        // rclcpp::NodeOptions().allow_undeclared_parameters(true)被调用
        this->set_parameter(rclcpp::Parameter("width", 1.55));
    }
    // 3-2.查；
    void get_param() {
        RCLCPP_INFO(this->get_logger(),
                    "------------------------查-----------------------");
        // this->get_parameter()根据键来查询具体对象
        // this->get_parameters()根据由键组成的vector来查询一些对象
        // this->has_parameter()根据键来查询并判断是否存在这个参数

        // 获取指定参数
        auto car = this->get_parameter("car_name");
        RCLCPP_INFO(this->get_logger(), "key = %s, value = %s",
                    car.get_name().c_str(), car.as_string().c_str());
        // 获取一些参数
        auto param1 = this->get_parameters({"car_name", "height", "wheels"});
        for (auto &&param : param1) {
            RCLCPP_INFO(this->get_logger(), "(%s = %s)",
                        param.get_name().c_str(),
                        param.value_to_string().c_str());
        }
        // 判断是否包含
        RCLCPP_INFO(this->get_logger(), "是否包含 car_name? %d",
                    this->has_parameter("car_name"));
        RCLCPP_INFO(this->get_logger(), "是否包含 width?%d",
                    this->has_parameter("width"));
    }
    // 3-3.改；
    void update_param() {
        RCLCPP_INFO(this->get_logger(),
                    "------------------------改-----------------------");
        this->set_parameter(rclcpp::Parameter("height", 1.65));
        RCLCPP_INFO(this->get_logger(), "height = %.2f",
                    this->get_parameter("height").as_double());
    }
    // 3-4.删;
    void del_param() {
        RCLCPP_INFO(this->get_logger(),
                    "------------------------删-----------------------");
        //可以删除未声明的参数（set_parameter）
        this->undeclare_parameter("width");
        RCLCPP_INFO(this->get_logger(),"width? %d",this->has_parameter("width"));

        //不能删除声明的参数（declare_parameter）
        // this->undeclare_parameter("car_name");
        // RCLCPP_INFO(this->get_logger(),"car_name? %d",this->has_parameter("car_name"));
    }
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    auto node = std::make_shared<ParamServer>();
    node->declare_param();
    node->get_param();
    node->update_param();
    node->del_param();
    rclcpp::spin(node);
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
