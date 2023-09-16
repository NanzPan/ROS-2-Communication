/* 
    问题：Time 和 Duration 有什么区别？
    答：
        1. 二者api使用类似；
        2. 二者有本质区别；
        rclcpp::Time t2(2, 500000000L);-----指一个具体时刻 --- 1970-01-01 00::00::02::500
        rclcpp::Duration du2(2, 500000000);------指的是一个时间段，持续2.5s。

 */
// 1.包含头文件;
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

// 3.定义节点类；
class MyNode : public rclcpp::Node {
   public:
    MyNode() : Node("time_node_cpp") {
        // demo_rate();
        // demo_time();
        // demo_duration();
        demo_opt();
        
    }
    // 演示 Rate 的使用
   private:
    void demo_rate() {
        // 1. 创建 Rate 对象
        // 设置休眠时间（字面常量+时间单位）
        rclcpp::Rate rate1(500ms);
        // 设置执行频率（float数据）
        rclcpp::Rate rate2(1.0);
        // 2. 调用 Rate 的 sleep 函数
        while (rclcpp::ok()) {
            RCLCPP_INFO(this->get_logger(), "-----------------");
            // rate1.sleep();
            rate2.sleep();
        }
    }
    // 演示time的使用
    void demo_time() {
        // 1， 创建 Time 对象；
        //  1 秒 = 10亿 纳秒;
        rclcpp::Time t1(500000000L);
        rclcpp::Time t2(2, 500000000L);
        rclcpp::Time right_now = this->now();

        // 2 . 调用 Time 对象函数
        // 获取的 秒 是浮点类型的, 纳秒 是长整形的；
        RCLCPP_INFO(this->get_logger(), "s = %.2f , ns = %ld", t1.seconds(),
                    t1.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "s = %.2f , ns = %ld", t2.seconds(),
                    t2.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "s = %.2f , ns = %ld",
                    right_now.seconds(), right_now.nanoseconds());
    }

    // Duration的使用
    void demo_duration() {
        // 1. 创建 Duration 对象
        rclcpp::Duration du1(1s);
        rclcpp::Duration du2(2, 500000000);
        // 2. 调用函数
        RCLCPP_INFO(this->get_logger(), "s = %.2f , ns = %ld", du1.seconds(),
                    du1.nanoseconds());
        RCLCPP_INFO(this->get_logger(), "s = %.2f , ns = %ld", du2.seconds(),
                    du2.nanoseconds());
    }
    //运算符的使用
    void demo_opt(){
        rclcpp::Time t3(3,0);
        rclcpp::Time t4(10,0);

        rclcpp::Duration du3(3,0);
        rclcpp::Duration du4(15,0);

        //运算  
        //比较运算
        RCLCPP_INFO(this->get_logger(), "t1 >= t2 ? %d",t3 >= t4);
        RCLCPP_INFO(this->get_logger(), "t1 < t2 ? %d",t3 < t4);

        //数学运算
        //时刻相减为Duration，time不能和time相加； 秒 的话都是%.2f
        //Time与Time相减，Time 与 Duration 加减
        rclcpp::Duration du5 = t4 - t3;
        rclcpp::Time t5 = t4 + du3;
        rclcpp::Time t6 = t4 - du4;
        RCLCPP_INFO(this->get_logger(), "du5 = t4 - t3 = %.2f",du5.seconds());
        RCLCPP_INFO(this->get_logger(), "t5 = t4 + du3 = %.2f",t5.seconds());
        RCLCPP_INFO(this->get_logger(), "t6 = t4 - du4 = %.2f",t6.seconds());

        RCLCPP_INFO(this->get_logger(), "du3 < du4 ? %d",du3 < du4);
        RCLCPP_INFO(this->get_logger(), "du3 > du4 ? %d",du3 >= du4);
        rclcpp::Duration du6 = du3 * 3;       
        RCLCPP_INFO(this->get_logger(), "du6 = du3 * 3 = %.2f",du6.seconds());
        
    }
   
};
int main(int argc, char const *argv[]) {
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc, argv);
    // 4.调用spin函数，并传入节点对象指针;
    rclcpp::spin(std::make_shared<MyNode>());
    // 5.释放资源.
    rclcpp::shutdown();

    return 0;
}
