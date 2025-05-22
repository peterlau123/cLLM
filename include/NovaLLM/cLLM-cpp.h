#pragma once
#include <memory>
#include <string>

#include "config.h"
#include "utils/macros.h"

namespace cllm {

class Impl;

class CLLM_API Engine {
 public:
  Engine();

  ~Engine();

  bool init();

  // Load a model from a file
  bool parse(const std::string& modelPath);

  std::string chat(const std::string& prompt);

 private:
  Impl* impl_;  // Pointer to the implementation details
};

}  // namespace cllm
