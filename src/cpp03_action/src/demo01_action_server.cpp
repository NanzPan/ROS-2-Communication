/*
需求：编写动作服务端，需要解析客户端提出来的数字，并求和最终结果响应客户端，并形成连续反馈。

分析：
    1. 创建action服务端对象；
    2. 处理提交的目标值；
    3. 生成连续反馈；
    4. 响应最终结果；
    5. 处理取消请求。
流程：
    1.包含头文件；
    2.初始化 ROS2 客户端；
    3.定义节点类；
        3-1. 创建action服务端对象；
        3-2. 处理提交的目标值回调函数；
        3-3. 处理取消请求（回调函数）。
        3-4. 生成连续反馈和最终响应回调函数；
    4.调用spin函数，并传入节点对象指针；
    5.释放资源。
*/
// 1.包含头文件;
#include "base_interfaces_demo/action/progress.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using base_interfaces_demo::action::Progress;
using std::placeholders::_1;
using std::placeholders::_2;

// 3.定义节点类；
class ProgressActionServer : public rclcpp::Node {
   public:
    ProgressActionServer() : Node("progress_action_server_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "action 服务端创建！");
        // 3-1. 创建action服务端对象；
        /*提示
        rclcpp_action::Server<ActionT>::SharedPtr   返回值
        create_server<ActionT,NodeT>    模版
        (NodeT  node,    this
        const std::string &name,    话题名称
        rclcpp_action::Server<ActionT>::GoalCallback handle_goal,
        rclcpp_action::Server<ActionT>::CancelCallback handle_cancel,
        //三个回调函数 rclcpp_action::Server<ActionT>::AcceptedCallback
        handle_accepted, const rcl_action_server_options_t &options =
        rcl_action_server_get_default_options(),
        rclcpp::CallbackGroup::SharedPtr group = nullptr)
         */
        server_ = rclcpp_action::create_server<Progress>(
            this, "get_sum",
            std::bind(&ProgressActionServer::handle_goal, this, _1, _2),
            std::bind(&ProgressActionServer::handle_cancel, this, _1),
            std::bind(&ProgressActionServer::handle_accept, this, _1));
    }
    /*定义
    std::function<GoalResponse(const GoalUUID &, std::shared_ptr<const typename
    ActionT::Goal>)>;
     */
    // 3-2. 处理提交的目标值（回调函数)；
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const Progress::Goal> goal) {
        // 业务逻辑：判断提交的数字是否大于1，是才接收
        (void)uuid;
        if (goal->num <= 1) {
            RCLCPP_WARN(this->get_logger(), "提交的的目标值必须大于1！");
            return rclcpp_action::GoalResponse::REJECT;
        };
        // ACCEPT_AND_EXECUTE是接收马上执行, ACCEPT_AND_DEFER是接收推迟执行。
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    /*
       std::function<CancelResponse(std::shared_ptr<ServerGoalHandle<ActionT>>)>;
        */
    // 3-3。 处理取消请求（回调函数)
    rclcpp_action::CancelResponse handle_cancel(
        std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>>
            goal_handle1) {
        (void)goal_handle1;
        RCLCPP_INFO(this->get_logger(), "接受任务取消请求！");
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    /*
    std::function<void (std::shared_ptr<ServerGoalHandle<ActionT>>)>;
     */
    // 3-4. 生成连续反馈和最终响应（回调函数)；
    void execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>>
                     goal_handle2) {
        // 1. 生成连续反馈给client；

        /*
        publish_feedback函数提示：
        publish_feedback(std::shared_ptr<base_interfaces_demo::action::Progress_Feedback>
        feedback_msg)
        */

        // goal_handle->publish_feedback() __生成连续反馈的api。
        // 首先获取目标值，然后遍历，遍历中进行累加，每循环一次就计算进度，并作为连续反馈发布
        int num = goal_handle2->get_goal()->num;
        int sum = 0;
        auto feedback = std::make_shared<Progress::Feedback>();
        auto result = std::make_shared<Progress::Result>();

        // 设置休眠（每次累加都是耗时操作，为了看出来效果加休眠）1.0意味着1hz
        rclcpp::Rate rate(1.0);
        for (int i = 1; i <= num; i++) {
            sum += i;
            double progress = i / (double)num;  // 计算进度
            feedback->progress = progress;
            goal_handle2->publish_feedback(feedback);
            RCLCPP_INFO(this->get_logger(), "连续反馈中！进度：%.2f", progress);

            // 判断是否接收到取消请求

            // goal_handle->is_canceling()
            /*
            void
            canceled(std::shared_ptr<base_interfaces_demo::action::Progress_Result>
            result_msg)
             */
            // goal_handle->canceled(,)

            if (goal_handle2->is_canceling()) {
                // 有则终止程序--return
                result->sum = sum;
                goal_handle2->canceled(result);
                RCLCPP_INFO(this->get_logger(), "任务强制被取消！");
                return;
            }

            rate.sleep();
        }

        // 2. 生成最终响应结果。

        /*
        succeed()函数提示：
        succeed(std::shared_ptr<base_interfaces_demo::action::Progress_Result>
        result_msg)
         */
        // goal_handle->succeed()__生成最终响应结果的api。
        if (rclcpp::ok()) {
            auto result2 = std::make_shared<Progress::Result>();
            result2->sum = sum;
            goal_handle2->succeed(result2);
            RCLCPP_INFO(this->get_logger(), "最终响应结果：%d", sum);
        }
    }
    void handle_accept(
        std::shared_ptr<rclcpp_action::ServerGoalHandle<Progress>>
            goal_handle2) {
        // 新建线程处理耗时的主逻辑实现；
        std::thread(
            std::bind(&ProgressActionServer::execute, this, goal_handle2))
            .detach();
    }

   private:
    rclcpp_action::Server<Progress>::SharedPtr server_;
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；s
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    rclcpp::spin(std::make_shared<ProgressActionServer>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
