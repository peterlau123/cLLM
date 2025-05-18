#pragma once
#include <memory>

#include "cLLM/common/device.h"

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

  /**
   * @brief 分配指定大小的内存
   * @param size 要分配的字节数
   * @param[out] data 指向分配内存的指针的指针
   * @throw std::bad_alloc 内存分配失败时抛出
   * @see <a href="https://en.cppreference.com/w/cpp/memory/new/operator_new">operator new[]</a>
   * @todo 参考https://github.com/microsoft/mimalloc，tcmalloc和jellalloc，优化当前alloc实现
   */
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