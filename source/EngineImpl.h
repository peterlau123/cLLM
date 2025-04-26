#pragma once
#include <string>

#include "parser.h"
#include "pipeline.h"

namespace cllm {

  class EngineImpl {
  public:
    EngineImpl() = default;

    bool init();

    void parse(const std::string& modelPath);

    std::string chat(const std::string& prompt);

  private:
    ParserPtr parser_;
    PipelinePtr pipeline_;
  };

}  // namespace cllm