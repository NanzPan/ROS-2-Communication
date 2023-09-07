      /*
需求：编写服务端实现，解析提交的 请求数据，将解析的数据相加并响应到客户端。
步骤：
   1.包含头文件；
   2.初始化 ROS2 客户端；
   3.定义节点类；
          3-1.创建服务端
          3-2.回调函数解析请求并发送响应
   4.调用spin函数，并传入节点对象指针；
   5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/addint.hpp"

using base_interfaces_demo::srv::Addint;
using std::placeholders::_1;
using std::placeholders::_2;

// 3.定义节点类；
class AddintServer : public rclcpp::Node {
public:
    AddintServer() : Node("add_int_Server_node_cpp") {
    RCLCPP_INFO(this->get_logger(),"服务端节点创建：！");
          // 3-1.创建服务端
          /* 
              模版：服务接口类型；
              参数：
                1.服务话题；
                2.回调函数。
              返回值：服务对象指针。
          */
          server_ = this->create_service<Addint>("add_ints",std::bind(&AddintServer::add,this,_1,_2));
  }
          // 3-2.回调函数解析请求并发送响应
  void add(const Addint::Request::SharedPtr req, const Addint::Response::SharedPtr res){
          res -> num3 = req -> num1 + req -> num2;
          RCLCPP_INFO(this->get_logger(), "%d + %d = %d",req->num1, req->num2, res->num3);
  }
private:
  rclcpp::Service<Addint>::SharedPtr server_;  //在节点类中创建服务对象server_去接收服务端信息
};
int main(int argc, char const *argv[]) {
   // 2.初始化 ROS2 客户端；s
  rclcpp::init(argc, argv);
   // 4.调用spin函数，并传入节点对象指针;
   rclcpp::spin(std::make_shared<AddintServer>());
   // 5.释放资源.
   rclcpp::shutdown();
 
    return 0;
}
 