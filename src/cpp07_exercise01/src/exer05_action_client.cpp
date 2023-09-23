      /*
需求：向动作服务端传入目标点数据，并处理响应结束
步骤：
   0.解析launch文件传入的参数
   1.包含头文件；
   2.初始化 ROS2 客户端；
   3.定义节点类；
        3-1. 创建动作客户端
        3-2. 连接服务端，发送请求；
        3-3. 处理关于目标值的响应结果；
        3-4. 处理连续反馈；
        3-5，处理最终反应
   4.调用spin函数,并传入节点对象指针;
   5.释放资源。
*/
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "base_interfaces_demo/action/nav.hpp"

using base_interfaces_demo::action::Nav;
using namespace::std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

// 3.定义节点类；
class Exer05ActionClient : public rclcpp::Node {
public:
    Exer05ActionClient() : Node("exer05_action_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "案例3客户端建立！");
        // 3-1. 创建动作客户端
        client_ = rclcpp_action::create_client<Nav>(this,"nav");
        // 3-2. 连接服务端，发送请求；
    }
        void send_goal(float x,float y,float theta){
            if(!client_->wait_for_action_server(10s))
            {
            //连接服务端
            RCLCPP_INFO(this->get_logger(), "服务连接超时！");
            return;
            }
        
            // 调用动作客户端的发送请求
            Nav::Goal goal;
            goal.goal_x = x;
            goal.goal_y = y;
            goal.goal_theta = theta;
            rclcpp_action::Client<Nav>::SendGoalOptions options;
            //处理目标值
            options.goal_response_callback = std::bind(&Exer05ActionClient::goal_response_callback,this,_1);
            // 处理连续反馈函数
            options.feedback_callback = std::bind(&Exer05ActionClient::feedback_callback, this,_1, _2);
            // 处理最终反应
            options.result_callback = std::bind(&Exer05ActionClient::result_callback,this,_1);
            client_->async_send_goal(goal, options);

        }
        
        // 3-3. 处理关于目标值的响应结果；
        void goal_response_callback(std::shared_ptr<rclcpp_action::ClientGoalHandle<Nav>> goal_handle01){
            if (!goal_handle01) {
                RCLCPP_INFO(this->get_logger(),"请求目标非法！");
            }
            else {
                RCLCPP_INFO(this->get_logger(), "数据被接受！");
            }
        };
        // 3-4. 处理连续反馈；
        void feedback_callback(std::shared_ptr<rclcpp_action::ClientGoalHandle<Nav>> goal_handle,std::shared_ptr < const Nav::Feedback> feedback){ 
            (void)goal_handle;
            RCLCPP_INFO(this->get_logger(), "剩余 %.2f 米",feedback->distance);
        };
        // 3-5，处理最终反应
        void result_callback(const rclcpp_action::ClientGoalHandle < Nav >::WrappedResult &result){
            if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
                //成功响应
                RCLCPP_INFO(this->get_logger(), "乌龟的最终位姿信息，坐标：（%.2f,%.2f）,航向：%.2f",result.result->turtle_x,result.result->turtle_y,result.result->turtle_theta);
            } 
            else{
                // 响应失败
                RCLCPP_INFO(this->get_logger(), "响应失败！");
            }
        };
        
private:
    rclcpp_action::Client<Nav>::SharedPtr client_;
};

int main(int argc, char const *argv[]) {

   // 0.解析launch文件传入的参数 
    if (argc != 5) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "请输入合法的目标点数据");
        return 1;
    }

   // 2.初始化 ROS2 客户端；
  rclcpp::init(argc, argv);
   // 4.调用spin函数,并传入节点对象指针;
   auto client = std::make_shared<Exer05ActionClient>();
   client-> send_goal(atof(argv[1]),atof(argv[2]),atof(argv[3]));
   rclcpp::spin(client);
   // 5.释放资源.
   rclcpp::shutdown();
 
    return 0;
}
 