#pragma once

#include "NovaLLM/common/device.h"
#include "NovaLLM/data/tensor.h"
#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/model/model.h"
#include "NovaLLM/utils/macros.h"

namespace nova_llm {

class Impl;

class NOVA_LLM_API Engine {
 public:
  Engine() = default;

  ~Engine();

  bool init();
  void run();

 private:
  Impl* impl_;
};


}  // namespace nova_llm
