#include "NovaLLM/memory/buffer_manager.h"

#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/utils/macros.h"
#include "buffer_hub.h"

namespace nova_llm {


BufferManager &BufferManager::Builder::build(const nova_llm::BufferManager::Config &config) {
  static BufferManager buffer_manager;
  if (!buffer_manager.isInited()) {
    auto ret = buffer_manager.init(config);
  }
  return buffer_manager;
}

bool BufferManager::init(const nova_llm::BufferManager::Config &config) {
  bool ret = false;
  if (config.device_flags.has(DeviceType::CPU)) {
    BufferHub::Config cfg;
    cfg.allocator = config.cpu.alloc;
    buffer_hubs_[DeviceType::CPU] = BufferHub::Builder::build(cfg);
  }
  return ret;
}

void BufferManager::put(const Buffer &buffer) {}

Buffer BufferManager::fetch(size_t size, DeviceType device_type) {
  Buffer buffer;
  Size sz(size);
  auto block_ptr=buffer_hubs_[device_type]->getBlock(sz);
  buffer.data=block_ptr->data;
  buffer.size=block_ptr->size;

  return buffer;
}

BufferManager::~BufferManager() {
  for (auto p : buffer_hubs_) {
    BufferHub::Builder::destroy(&(p.second));
  }
}


}  // namespace nova_llm