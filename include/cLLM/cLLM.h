#pragma once
#include <string>
#include <memory>

#include "define.h"

namespace cllm {

  class CLLM_API  cLLM {
  public:
    cLLM() = default;

    ~cLLM() = default;

    // Load a model from a file
    bool loadModel(const std::string& modelPath);

  private:
    using cLLMImpl = std::unique_ptr<struct cLLMImpl>;
    cLLMImpl impl;  // Pointer to the implementation details
  };

}  // namespace cllm
