#pragma once
#include <memory>
#include <string>

#include "config.h"
#include "util/macros.h"

namespace cllm {
  class EngineImpl;
  class CLLM_API Engine {
  public:
    Engine() = default;

    ~Engine() = default;

    bool init();

    // Load a model from a file
    bool loadModel(const std::string& modelPath);

  private:
    using EngineImplPtr = std::unique_ptr<class EngineImpl>;
    EngineImplPtr impl_;  // Pointer to the implementation details
  };

}  // namespace cllm
