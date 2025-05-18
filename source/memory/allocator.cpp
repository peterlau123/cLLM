#include "cLLM/memory/allocator.h"

#include <new>
#include <string>

namespace cllm {
// 使用 CRTP 调用派生类的实现
template <typename Derived>
void AllocatorBase<Derived>::alloc(int size, uint8_t** data) {
  static_cast<Derived*>(this)->alloc_impl(size, data);
}

template <typename Derived>
void AllocatorBase<Derived>::dealloc(uint8_t** data) {
  static_cast<Derived*>(this)->dealloc_impl(data);
}

// 获取分配器类型
template <typename Derived>
DeviceType AllocatorBase<Derived>::get_device_type() const {
  return static_cast<const Derived*>(this)->get_device_type_impl();
}

void CPUAllocator::alloc_impl(int size, uint8_t** data) {
  try {
    *data = new uint8_t[size];
  } catch (const std::bad_alloc& e) {
    throw std::runtime_error("CPU memory allocation failed: " + std::string(e.what()));
  }
}

void CPUAllocator::dealloc_impl(uint8_t** data) {
  if (data && *data) {
    delete[] static_cast<uint8_t*>(*data);
    *data = nullptr;
  }
}

DeviceType CPUAllocator::get_device_type_impl() const { return DeviceType::CPU; }

}  // namespace cllm