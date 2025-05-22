#pragma once

#include "NovaLLM/common/device.h"
#include "NovaLLM/data/tensor.h"
#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/model/model.h"
#include "NovaLLM/utils/macros.h"

namespace nova_llm {

class NOVA_LLM_API Engine {
 public:
  Engine() = default;
  virtual ~Engine() = default;

  virtual bool init() = 0;
  virtual bool isAvailable() const = 0;
  virtual DeviceType type() const = 0;
};

using EnginePtr = std::shared_ptr<Engine>;

}  // namespace nova_llm
