/*
需求：填写客户端，可以发送一个整形数据给服务端，并处理服务端的连续反馈和最终响应
流程：
    前提：可以解析终端中动态传入的参数。
    1.包含头文件；
    2.初始化 ROS2 客户端；
    3.定义节点类；
        3-1. 创建动作客户端
        3-2. 发送请求
        3-3. 处理关于目标值的服务器响应 （回调函数）
        3-4. 处理连续反馈（回调函数）
        3-5. 处理最终响应（回调函数）


4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
// 1.包含头文件;
#include "base_interfaces_demo/action/progress.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using base_interfaces_demo::action::Progress;
using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

// 3.定义节点类；
class ProgressActionClient : public rclcpp::Node {
   public:
    ProgressActionClient() : Node("progress_action_client_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "action 客户端创建！");
        // 3-1. 创建动作客户端
        /*
        rclcpp_action::Client<ActionT>::SharedPtr create_client<ActionT,
        NodeT>(NodeT node, const std::string &name,
        rclcpp::CallbackGroup::SharedPtr group = nullptr, const
        rcl_action_client_options_t &options =
        rcl_action_client_get_default_options())
         */
        client_ = rclcpp_action::create_client<Progress>(this, "get_sum");
    }
    // 3-2. 发送请求（num是请求时的goalnum）
    void send_goal1(int num) {
        // 1.连接服务端
        if (!client_->wait_for_action_server(10s)) {
            RCLCPP_ERROR(this->get_logger(), "服务连接失败！");
            return;
        }
        // 2. 发送具体请求
        /*
        std::shared_future<rclcpp_action::ClientGoalHandle<base_interfaces_demo::action::Progress>::SharedPtr>
        async_send_goal(
        const base_interfaces_demo::action::Progress::Goal&goal,
        const
        rclcpp_action::Client<base_interfaces_demo::action::Progress>::SendGoalOptions&options)
         */
        auto goal = Progress::Goal();
        goal.num = num;
        rclcpp_action::Client<Progress>::SendGoalOptions options;
        options.goal_response_callback =
            std::bind(&ProgressActionClient::goal_response_callback, this, _1);
        options.feedback_callback =
            std::bind(&ProgressActionClient::feedback_callback, this, _1, _2);
        options.result_callback =
            std::bind(&ProgressActionClient::result_callback, this, _1);
        auto future1 = client_->async_send_goal(goal, options);
    }
    // 3-3. 处理关于目标值的服务器响应 （回调函数）
    /*
        using GoalHandle = ClientGoalHandle<ActionT>;
        using GoalResponseCallback =
        std::function<void (typenameGoalHandle::SharedPtr)>;
     */
    void goal_response_callback(
        rclcpp_action::ClientGoalHandle<Progress>::SharedPtr res_cb) {
        // 客户端发送目标给服务端，服务端会判断目标是否可以被接收
        // 可以的话就会响应回给客户端，此时参数里面会有内容
        // 拒绝了的话会响应回来的参数就是空指针
        // 所以我们可以判断是否接收目标
        if (!res_cb) {
            // 是空指针的话就相当于！0就是true
            RCLCPP_ERROR(this->get_logger(), "目标请求被服务端拒绝！");
        } else {
            RCLCPP_INFO(this->get_logger(), "目标处理中！");
        }
    }
    // 3-4. 处理连续反馈（回调函数）
    /*
    std::function<void (
        typename ClientGoalHandle<ActionT>::SharedPtr,
        const std::shared_ptr<const Feedback>)>;
     */
    void feedback_callback(
        rclcpp_action::ClientGoalHandle<Progress>::SharedPtr feedback_cb,
        const std::shared_ptr<const ::Progress::Feedback> feedback) {
        (void)feedback_cb;
        int progress = feedback->progress * 100;
        RCLCPP_INFO(this->get_logger(), "当前进度是：%d%%", progress);
    }
    // 3-5. 处理最终响应（回调函数)
    /*
    std::function<void (const WrappedResult & result)>;
     */
    void result_callback(
        const rclcpp_action::ClientGoalHandle<Progress>::WrappedResult
            &result) {
        // 处理连续反馈之后的响应结果
        // result是对响应的结果进行了封装；
        // result的结果可以是任务被取消，任务结束等，所以我们要知道他的状态码result.code；
        if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
            RCLCPP_INFO(this->get_logger(), "最终结果：%d", result.result->sum);
        } else if (result.code == rclcpp_action::ResultCode::ABORTED) {
            RCLCPP_INFO(this->get_logger(), "执行被中断！");
        } else if (result.code == rclcpp_action::ResultCode::CANCELED) {
            RCLCPP_INFO(this->get_logger(), "执行被取消！");
        } else {
            RCLCPP_INFO(this->get_logger(), "未知错误！");
        }
    }

   private:
    rclcpp_action::Client<Progress>::SharedPtr client_;
};
int main(int argc, char const *argv[]) {
    if (argc != 2) {
        RCLCPP_ERROR(rclcpp::get_logger("error1"), "请提交一个整形数据！");
        return 1;
        // 返回 1
        // 表示程序以错误状态退出。通常，非零的返回值表示程序出现了错误，而零表示成功
    }
    // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    auto node = std::make_shared<ProgressActionClient>();
    node->send_goal1(atoi(argv[1]));
    // 这行代码的作用是通过指针 node 访问 ProgressActionClient 对象的成员函数
    // send_goal1，并将 atoi(argv[1]) 解析后的整数值作为参数传递给这个函数。
    //  argv可以获取send_goal1 的整形数据；是请求时的goalnum
    rclcpp::spin(node);
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
