#pragma once
#include <memory>
#include <string>

#include "config.h"
#include "utils/macros.h"

namespace cllm {
  class EngineImpl;
  class CLLM_API Engine {
  public:
    Engine() = default;

    ~Engine() = default;

    bool init();

    // Load a model from a file
    bool parse(const std::string& modelPath);

    std::string chat(const std::string& prompt);

  private:
    using EngineImplPtr = std::unique_ptr<class EngineImpl>;
    EngineImplPtr impl_;  // Pointer to the implementation details
  };

}  // namespace cllm
