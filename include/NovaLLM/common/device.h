#pragma once

#include "NovaLLM/utils/macros.h"

namespace nova_llm {

enum class DeviceType { CPU = 0, CUDA, METAL, UNKNOWN };

class NOVA_LLM_API Device {
 public:
  Device() = default;
  virtual ~Device() = default;

  virtual bool init() = 0;
  virtual bool isAvailable() const = 0;
  virtual DeviceType type() const = 0;
};

using DevicePtr = std::shared_ptr<Device>;

}  // namespace nova_llm