#pragma once

namespace cllm {

enum class DeviceType : uint32_t { UNKNOWN = 0, CPU = 0x1, GPU = 0x2, METAL = 0x4 };

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

}  // namespace cllm