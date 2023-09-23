/*
需求：处理客户端发送的目标点，控制乌龟运动到点，并反馈实时距离
步骤：
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
  3-1 . 创建原乌龟订阅方，获取当前坐标
  3-2 . 创建速度指令发布方，控制乌龟运动
  3-3 . 创建动作客户端
  3-4 . 解析动作客户端提交的数据
  3-5 . 处理客户端取消指令操作
  3-6 . 实现主逻辑（耗时操作），启动子线程
  3-7 . 子线程中，发布速度指令，产生连续反馈，响应输出
4.调用spin函数,并传入节点对象指针;
5.释放资源。
*/
// 1.包含头文件;
#include "base_interfaces_demo/action/nav.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "turtlesim/msg/pose.hpp"

using base_interfaces_demo::action::Nav;
using geometry_msgs::msg::Twist;
using std::placeholders::_1;
using std::placeholders::_2;
using turtlesim::msg::Pose;
// 3.定义节点类；
class Exer04ActionServer : public rclcpp::Node {
   public:
    Exer04ActionServer() : Node("exer04_action_server_node_cpp") {
        RCLCPP_INFO(this->get_logger(), "案例3服务端建立！");
        // 3-1 . 创建原乌龟订阅方，获取当前坐标
        sub_ = this->create_subscription<Pose>(
            "/turtle1/pose", 10,
            std::bind(&Exer04ActionServer::pose_cb, this, _1));
        // 3-2 . 创建速度指令发布方，控制乌龟运动
        cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/turtle1/cmd_vel", 10);
        // 3-3 . 创建动作客户端
        action_server_ = rclcpp_action::create_server<Nav>(
            this, "/nav",
            std::bind(&Exer04ActionServer::handle_goal, this, _1, _2),
            std::bind(&Exer04ActionServer::handle_cancel, this, _1),
            std::bind(&Exer04ActionServer::handle_accepted, this, _1));
        // 3-4 . 解析动作客户端提交的数据
        // 3-5 . 处理客户端取消指令操作
        // 3-6 . 实现主逻辑（耗时操作），启动子线程
        // 3-7 . 子线程中，发布速度指令，产生连续反馈，响应输出
    }

   private:
    rclcpp::Subscription<Pose>::SharedPtr sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
    rclcpp_action::Server<Nav>::SharedPtr action_server_;
    float x, y;
    void pose_cb(const turtlesim::msg::Pose::SharedPtr pose) {
        x = pose->x;
        y = pose->y;
    }
    // 请求目标处理
    // std::function<GoalResponse(const GoalUUID &, std::shared_ptr<const
    // typename ActionT::Goal>)>;
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const Nav::Goal> goal) {
        (void)uuid;
        (void)goal;
        // 取出目标中的x，y坐标，判断是否超出范围【0，11.08】
        if (goal->goal_x < 0 || goal->goal_x > 11.08 || goal->goal_y > 11.08 ||
            goal->goal_y < 0) {
            RCLCPP_INFO(this->get_logger(), "目标点非法！");
            return rclcpp_action::GoalResponse::REJECT;
        }
        RCLCPP_INFO(this->get_logger(), "目标点合法！");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;

        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    // 取消请求处理
    // std::function<CancelResponse(std::shared_ptr<ServerGoalHandle<ActionT>>)>;
    rclcpp_action::CancelResponse handle_cancel(
        std::shared_ptr<rclcpp_action::ServerGoalHandle<Nav>> goal_handle1) {
        (void)goal_handle1;
        RCLCPP_INFO(this->get_logger(), "任务取消！");
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    // 主逻辑处理
    void execute(
        std::shared_ptr<rclcpp_action::ServerGoalHandle<Nav>> goal_handle2) {
        // 子线程处理
        RCLCPP_INFO(this->get_logger(), "主逻辑开始执行");
        // 最终结果
        // 创建最终结果对象，连续反馈对象，速度指令对象（twist）
        auto result = std::make_shared<Nav::Result>();
        auto feedback = std::make_shared<Nav::Feedback>();
        geometry_msgs::msg::Twist twist;
        // 1.生成连续反馈
        // 频率控制Rate
        rclcpp::Rate rate(1.0);
        while (1) {
            // 取消请求，特殊处理
            if (goal_handle2->is_canceling()) {
                goal_handle2->canceled(result);
                return;
                // 当函数的返回类型是 void 时，可以使用 return;
            }
            // 解析原生乌龟坐标与目标点坐标
            float goal_x2 = goal_handle2->get_goal()->goal_x;
            float goal_y2 = goal_handle2->get_goal()->goal_y;
            // 计算剩余距离
            float distance_x = goal_x2 - x;
            float distance_y = goal_y2 - y;
            float distance =
                std::sqrt(distance_x * distance_x + distance_y * distance_y);
            feedback->distance = distance;
            goal_handle2->publish_feedback(feedback);
            // 根据剩余距离计算速度并发布
            float scale = 0.5;
            float linear_x = scale * distance_x;
            float linear_y = scale * distance_y;
            twist.linear.x = linear_x;
            twist.linear.y = linear_y;
            cmd_pub_->publish(twist);
            // 循环结束条件
            if (distance <= 0.05) {
                // 与目标点的剩余距离小于 0.05m，那么就结束导航;
                RCLCPP_INFO(this->get_logger(),
                            "导航完成，到达目标点，误差±5cm");
                break;
            }
            // 设置休眠,
            rate.sleep();
        };
        // 3.生成最终响应
        // 判断是否正常，正常就发送
        if (rclcpp::ok()) {
            result->turtle_x = x;
            result->turtle_y = y;
            goal_handle2->succeed(result);
        };
        // 2.发布乌龟指令
        //  std::function<void (std::shared_ptr<ServerGoalHandle<ActionT>>)>;
    }
    void handle_accepted(
        std::shared_ptr<rclcpp_action::ServerGoalHandle<Nav>> goal_handle3) {
        // (void)goal_handle3;
        std::thread(std::bind(&Exer04ActionServer::execute, this, goal_handle3))
            .detach();
    }
};

int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc, argv);
    // 4.调用spin函数,并传入节点对象指针;
    rclcpp::spin(std::make_shared<Exer04ActionServer>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
