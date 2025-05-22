#pragma once
#include <cstddef>
#include <cstdint>

namespace nova_llm {

struct Buffer {
  uint8_t* data {nullptr};
  size_t size = 0;  // in bytes
};


}  // namespace nova_llm