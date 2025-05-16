#pragma once
#include <string>
#include <vector>

#include "parser.h"
#include "pipeline.h"

namespace cllm {

class EngineImpl {
 public:
  EngineImpl() = default;

  bool init();

  bool parse(const std::string& modelPath);

  std::string chat(const std::string& prompt);

 private:
  std::vector<std::string> history_;
  ParserPtr parser_;
  PipelinePtr pipeline_;
};

}  // namespace cllm