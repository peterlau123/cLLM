#pragma once
#include <memory>

#include "cLLM/common/device.h"
#include "cLLM/utils/template.h"

namespace cllm {

class IAllocator {
 public:
  virtual ~IAllocator() = default;
  virtual void alloc(int size, uint8_t** data) = 0;
  virtual void dealloc(uint8_t** data) = 0;
  virtual DeviceType get_device_type() const = 0;
};

DEFINE_SHARED_PTR(IAllocator);

template <typename Derived>
class AllocatorBase : public IAllocator {
 public:
  AllocatorBase() = default;
  virtual ~AllocatorBase() = default;

  // 使用 CRTP 调用派生类的实现
  void alloc(int size, uint8_t** data);

  void dealloc(uint8_t** data);
  // 获取分配器类型
  DeviceType get_device_type() const;
};

class CPUAllocator : public AllocatorBase<CPUAllocator> {
 public:
  CPUAllocator() = default;
  ~CPUAllocator() override = default;

  void alloc_impl(int size, uint8_t** data);

  void dealloc_impl(uint8_t** data);

  DeviceType get_device_type_impl() const;
};

DEFINE_SHARED_PTR(CPUAllocator);

}  // namespace cllm