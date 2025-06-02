#pragma once
#include <cstddef>
#include <cstdint>

#include "NovaLLM/common/device.h"

namespace nova_llm {

struct Buffer {
  uint8_t* data {nullptr};
  size_t size = 0;  // in bytes
  DeviceType device_type = DeviceType::CPU;
};


}  // namespace nova_llm