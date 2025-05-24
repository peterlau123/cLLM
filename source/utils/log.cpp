#include "NovalLM/utils/log.h"

#include <fmt/format.h>

namespace nova_llm {

void Logger::init(const std::string& name,
                  const std::string& logFile,
                  spdlog::level::level_enum level) {
  try {
    // Refer to
    // https://github.com/gabime/spdlog?tab=readme-ov-file#logger-with-multi-sinks---each-with-a-different-format-and-log-level
    //  Create console sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(level);

    // Create file sink
    auto file_sink =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFile, 1024 * 1024 * 5, 3);
    file_sink->set_level(level);

    // Create a formatter
    auto formatter =
        std::make_shared<spdlog::pattern_formatter>("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");

    // Set formatter for both sinks
    console_sink->set_formatter(formatter);
    file_sink->set_formatter(formatter);

    // Create logger with both sinks
    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    logger_ = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
    logger_->set_level(level);
    logger_->flush_on(spdlog::level::info);

    // Set as default logger
    spdlog::set_default_logger(logger_);
  } catch (const spdlog::spdlog_ex& ex) {
    fmt::print("Log initialization failed: {}\n", ex.what());
  }
}

}  // namespace nova_llm