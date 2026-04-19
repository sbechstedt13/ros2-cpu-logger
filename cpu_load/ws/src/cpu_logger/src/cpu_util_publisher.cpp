#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "cpu_reader.cpp"

using namespace std::chrono_literals;

class CpuUtilLogger : public rclcpp::Node
{
public:
    CpuUtilLogger()
    : Node("cpu_util_publisher")
    {
        timer_ = this->create_wall_timer(
        5000ms, std::bind(&CpuUtilLogger::timer_callback, this));
        // Create custom logger
        logger_ = spdlog::basic_logger_mt("cpu_load", "logs/cpu_load.log");
    }

private:
    CpuReader cpu_reader;
    void timer_callback()
    {
        // Periodically log current CPU load
        logger_->info("{:.2f}%", cpu_reader.getCpuUsage());
    }
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<spdlog::logger> logger_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CpuUtilLogger>());
    rclcpp::shutdown();
    return 0;
}
