#pragma once

#include "NovaLLM/common/device.h"
#include "NovaLLM/utils/macros.h"

namespace nova_llm {

class NOVA_LLM_API Allocator {
 public:
  Allocator() = default;
  virtual ~Allocator() = default;

  virtual void* allocate(size_t size) = 0;
  virtual void deallocate(void* ptr) = 0;
  virtual bool isAvailable() const = 0;
};

using AllocatorPtr = std::shared_ptr<Allocator>;

}  // namespace nova_llm