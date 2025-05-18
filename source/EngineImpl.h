#pragma once
#include <string>
#include <vector>

#include "cLLM/parser/parser.h"
#include "cLLM/pipeline.h"

namespace cllm {

class EngineImpl {
 public:
  using EngineImplPtr = std::shared_ptr<EngineImpl>;

  static EngineImplPtr build();

  bool init();

  bool parse(const std::string& modelPath);

  std::string chat(const std::string& prompt);

  EngineImpl() = default;

 private:
  bool init_;
  std::vector<std::string> history_;
  ParserPtr parser_;
  PipelinePtr pipeline_;
};

using EngineImplPtr = EngineImpl::EngineImplPtr;

}  // namespace cllm