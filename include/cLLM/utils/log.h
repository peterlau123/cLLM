#pragma once
#include <spdlog/fmt/ostr.h>
#include <spdlog/formatter.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <memory>
#include <string>

namespace cllm {

class Logger {
 public:
  static Logger& getInstance() {
    static Logger instance;
    return instance;
  }

  void init(const std::string& name = "cLLM",
            const std::string& logFile = "cLLM.log",
            spdlog::level::level_enum level = spdlog::level::info);

  void setLevel(spdlog::level::level_enum level) {
    if (logger_) {
      logger_->set_level(level);
    }
  }

  template <typename... Args>
  void trace(const char* fmt, const Args&... args) {
    if (logger_) logger_->trace(fmt, args...);
  }

  template <typename... Args>
  void debug(const char* fmt, const Args&... args) {
    if (logger_) logger_->debug(fmt, args...);
  }

  template <typename... Args>
  void info(const char* fmt, const Args&... args) {
    if (logger_) logger_->info(fmt, args...);
  }

  template <typename... Args>
  void warn(const char* fmt, const Args&... args) {
    if (logger_) logger_->warn(fmt, args...);
  }

  template <typename... Args>
  void error(const char* fmt, const Args&... args) {
    if (logger_) logger_->error(fmt, args...);
  }

  template <typename... Args>
  void critical(const char* fmt, const Args&... args) {
    if (logger_) logger_->critical(fmt, args...);
  }

  void flush() {
    if (logger_) logger_->flush();
  }

 private:
  Logger() = default;
  ~Logger() = default;
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  std::shared_ptr<spdlog::logger> logger_;
};

}  // namespace cllm

// Convenience macros
#define LOG_TRACE(...) cllm::Logger::getInstance().trace(__VA_ARGS__)
#define LOG_DEBUG(...) cllm::Logger::getInstance().debug(__VA_ARGS__)
#define LOG_INFO(...) cllm::Logger::getInstance().info(__VA_ARGS__)
#define LOG_WARN(...) cllm::Logger::getInstance().warn(__VA_ARGS__)
#define LOG_ERROR(...) cllm::Logger::getInstance().error(__VA_ARGS__)
#define LOG_CRITICAL(...) cllm::Logger::getInstance().critical(__VA_ARGS__)

// Initialize logger macro
#define LOG_INIT(name, logFile, level) cllm::Logger::getInstance().init(name, logFile, level)

// Set log level macro
#define LOG_SET_LEVEL(level) cllm::Logger::getInstance().setLevel(level)

// Flush logs macro
#define LOG_FLUSH() cllm::Logger::getInstance().flush()
