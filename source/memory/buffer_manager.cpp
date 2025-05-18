#include "cLLM/memory/buffer_manager.h"

#include "buffer_hub.h"
#include "cLLM/memory/allocator.h"
#include "cLLM/utils/macros.h"

namespace cllm {

constexpr bool DeviceTypeFlags::has(DeviceType type) const {
  return (flags & static_cast<uint32_t>(type)) != 0;
}

// 添加设备
constexpr void DeviceTypeFlags::set(DeviceType type) { flags |= static_cast<uint32_t>(type); }

// 移除设备
constexpr void DeviceTypeFlags::clear(DeviceType type) { flags &= ~static_cast<uint32_t>(type); }

// 获取所有设备
constexpr DeviceType DeviceTypeFlags::get() const { return static_cast<DeviceType>(flags); }

BufferManager &BufferManager::Builder::build(const cllm::BufferManager::Config &config) {
  static BufferManager buffer_manager;
  if (!buffer_manager.isInited()) {
    auto ret = buffer_manager.init(config);
  }
  return buffer_manager;
}

bool BufferManager::init(const cllm::BufferManager::Config &config) {
  bool ret = false;
  if (config.device_flags.has(DeviceType::CPU)) {
    buffer_hubs_[DeviceType::CPU] = BufferHub::Builder::buildNative();
  }
  return ret;
}

void BufferManager::put(const Buffer &buffer) {}

BufferManager::Buffer BufferManager::fetch(size_t size, DeviceType device_type) {
  BufferManager::Buffer buffer;
  return buffer;
}

BufferManager::~BufferManager() {
  for (auto p : buffer_hubs_) {
    BufferHub::Builder::destroy(&(p.second));
  }
}


}  // namespace cllm