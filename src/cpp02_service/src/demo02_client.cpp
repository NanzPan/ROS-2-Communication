      /*
需求：创建客户端，组织数据并提交，然后处理响应结果（关注业务流程）

步骤：
    前提：main函数中需要判断提交的参数是否正确。

   1.包含头文件；
   2.初始化 ROS2 客户端；
   3.定义节点类；
        3-1.创建客户端
        3-2.连接服务器（对于服务通信而言，如果客户端无法连接服务器，那么不能发送请求）；
        3-3.发送请求；
   4.创建对象指针；
        需要调用连接服务的函数，根据连接结果来做下一步处理；
        连接服务后，调用请求发送函数；
        再处理响应结果。
   5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/addint.hpp"

using base_interfaces_demo::srv::Addint;
using namespace std::chrono_literals;

// 3.定义节点类；
class AddintClient : public rclcpp::Node {
public:
    AddintClient() : Node("add_int_client_node_cpp") {
        RCLCPP_INFO(this -> get_logger(),"客户端建立！");
        // 3-1.创建客户端
        /* 
            模版：服务接口；
            参数：服务话题名称；
            返回值：服务对象指针。
         */
        client_ = this->create_client<Addint>("add_ints");
    }
        // 3-2.连接服务器（对于服务通信而言，如果客户端无法连接服务器，那么不能发送请求）；
        /* 
            连接服务器实现，成功返回true。
         */
        bool connect_server(){
            //在指定超时时间内连接服务器，如果成功那么返回true，否则返回false。
            //client_-> wait_for_service(1s);
            while (!client_->wait_for_service(1s)) //循环以3秒为超时时间连接服务器，知道连接到服务器才退出循环。
            {
                // 对 ctrl+c操作做出特殊处理
                //1. 怎么判断 ctrl+c 按下？  2.如何处理？
                //按下ctrl+c 是结束ros2程序，意味着要释放资源，比如：关闭 context容器；
                if (!rclcpp::ok())
                {
                    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"强行终止客户端！");
                    return false;
                }
                
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务器连接中！");
            }
            return true;
        }
        // 3-3.发送请求；
        //编写发送请求函数。 ---- 参数是两个整形数据，返回值是提交请求后服务端的返回结果。
        rclcpp::Client<Addint>::FutureAndRequestId send_request(int num1, int num2) {
            //组织请求数据

            //发送
            /* 
                rclcpp::Client<base_interfaces_demo::srv::Addint>::FutureAndRequestId
                async_send_request<CallbackT, <unnamed>>
                (std::shared_ptr<base_interfaces_demo::srv::Addint_Request> request, CallbackT &&cb)
             */
            auto request = std::make_shared<Addint::Request>();
            request->num1 = num1;
            request->num2 = num2;
            return client_->async_send_request(request);
         }

private:
    rclcpp::Client<Addint>::SharedPtr client_;
};
int main(int argc, char const *argv[]) {
    if (argc !=  3)
    {   RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"请提交两个整形数字！");
        return 1;
    }
   // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
   //创建客户端对象
    auto client = std::make_shared<AddintClient> ();
    //调用客户端对象的连接服务器功能
    bool flag = client->connect_server();
    //根据连接结果做进一步处理
    if (!flag)
    {   
        /* 
            rclcpp::get_logger("name")创建 logger 对象不依赖于 context。
         */
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"连接服务器失败，程序退出！");
        return 0;
    }
    //执行后续操作.....
    //调用请求提交函数，接收并处理响应结果。
        auto future = client->send_request(atoi(argv[1]),atoi(argv[2]));
    //处理响应
    if (rclcpp::spin_until_future_complete(client,future) == rclcpp::FutureReturnCode::SUCCESS) {  //成功
        RCLCPP_INFO(client->get_logger(),"响应成功！sum = %d",future.get()->num3);
    }
    else //失败
    {
        RCLCPP_ERROR(client->get_logger(),"响应失败！");
    }
   // 5.释放资源.
    rclcpp::shutdown();
 
    return 0;
}
 