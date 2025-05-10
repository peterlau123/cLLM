#pragma once
#include <memory>

#include "../backend/device.h"

namespace cllm {
class Allocator {
public:
  Allocator() = default;
  virtual ~Allocator() = default;

  /*
   * @brief Allocates memory of the given size.
   * @param size Size of the memory to allocate in bytes.
   * @param data Pointer to the allocated memory.
   */
  virtual void alloc(int size, void** data) = 0;
  virtual void dealloc(void** data) = 0;
};
using AllocatorPtr = std::shared_ptr<Allocator>;

class CPUAllocator : public Allocator {
public:
  CPUAllocator();
  ~CPUAllocator() override;
  void alloc(int size, void** data) override;
  void dealloc(void** data) override;
};

class GPUAllocator : public Allocator {
public:
  GPUAllocator();
  ~GPUAllocator() override;
  void alloc(int size, void** data) override;
  void dealloc(void** data) override;
};

static AllocatorPtr getAllocator(DeviceType device_type) {
  switch (device_type) {
    case DeviceType::CPU:
      return std::make_shared<CPUAllocator>();
    // Add other device types as needed
    case DeviceType::GPU:
      return std::make_shared<GPUAllocator>();
    default:
      return nullptr;
  }
}
}  // namespace cllm