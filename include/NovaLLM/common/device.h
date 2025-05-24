#pragma once

#include "NovaLLM/utils/macros.h"

namespace nova_llm {

enum class DeviceType : uint32_t { UNKNOWN = 0, CPU, CUDA, METAL };

struct DeviceTypeFlags {
 public:
  [[nodiscard]] constexpr bool has(DeviceType type) const;

  void set(DeviceType type);

  void clear(DeviceType type);

  [[nodiscard]] constexpr DeviceType get() const;

 private:
  uint32_t flags_ = 0;
};

}  // namespace nova_llm