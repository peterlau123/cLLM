#pragma once
#include <cstddef>
#include <functional>
#include <unordered_map>

#include "cLLM/common/device.h"
#include "cLLM/memory/allocator.h"

namespace cllm {

class DeviceTypeFlags {
 public:
  constexpr DeviceTypeFlags() : flags(0) {}

  constexpr DeviceTypeFlags(DeviceType type) : flags(static_cast<uint32_t>(type)) {}

  // 检查是否支持设备
  constexpr bool has(DeviceType type) const;

  // 添加设备
  constexpr void set(DeviceType type);

  // 移除设备
  constexpr void clear(DeviceType type);

  // 获取所有设备
  constexpr DeviceType get() const;

 private:
  uint32_t flags;
};

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
