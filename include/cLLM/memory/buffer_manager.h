#pragma once
#include <cstddef>
#include <functional>
#include <unordered_map>

#include "cLLM/common/device.h"
#include "cLLM/memory/allocator.h"

namespace cllm {


/*
 * @todo: use segregated free list
 * */
class BufferHub;

class BufferManager {
 public:
  struct Config {
    DeviceTypeFlags device_flags;

    struct CPU {};

    struct GPU {};

    struct Metal {};
  };

  struct Buffer {
    uint8_t* data {nullptr};
    size_t size = 0;  // in bytes
  };

  class Builder {
   public:
    static BufferManager& build(const Config& config);
  };

  bool isInited() const { return is_init_; }

  Buffer fetch(size_t size, DeviceType device_type);

  void put(const Buffer& buffer);

  ~BufferManager();

 private:
  BufferManager() = default;
  BufferManager(const BufferManager&) = delete;             // Disable copy constructor
  BufferManager& operator=(const BufferManager&) = delete;  // Disable copy assignment
  BufferManager(BufferManager&&) = delete;                  // Disable move constructor
  BufferManager& operator=(BufferManager&&) = delete;       // Disable move assignment

  bool init(const Config& config);
  bool is_init_;
  std::unordered_map<DeviceType, BufferHub*> buffer_hubs_;
};

}  // namespace cllm
