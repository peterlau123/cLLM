#pragma once
#include <list>
#include <unordered_map>

#include "cLLM/common/device.h"
#include "cLLM/memory/allocator.h"
#include "cLLM/utils/template.h"

namespace cllm {
struct Block {
  uint8_t* data = nullptr;
  uint64_t size = 0;
  int32_t ref_cnt = 0;
};

class BufferHub {
 public:
  struct Size {
    uint16_t b = 64;
    uint16_t kb = 0;
    uint16_t mb = 0;
    uint16_t gb = 0;

    [[nodiscard]] uint64_t totalBytes() const {
      return (gb << 10) * 1024 * 1024 + (mb << 10) * 1024 + (kb << 10) + b;
    }
  };

  struct SizeHash {
    std::size_t operator()(const Size& s) const { return std::hash<uint64_t>()(s.totalBytes()); }
  };

  struct Config {
    DeviceType device_type;
    std::vector<Size> size_levels;
    Size size_limit {0, 0, 0, 4};  // Memory in buffer hub cannot exceed this limit
    float warning_level =
        0.95;  // Be cautious when memory in buffer hub exceeds size_limit*warning_level
    IAllocatorPtr allocator;
  };

  class Builder {
   public:
    static BufferHub* build(const Config& config);

    static void destroy(BufferHub** hub);
  };

  void setConfig(const Config& config) { m_config_ = config; }

  void addSizeLevel(const Size& level_sz);

  void eraseSizeLevel(const Size& level_sz);

  Block getBlock(const Size& sz);

  void putBlock(const Block& block);

 private:
  void coalesce();

  [[nodiscard]] Size gradeLevel(const Size& sz) const;

  BufferHub() = default;
  std::unordered_map<Size, std::list<Block>, SizeHash> buffers_;
  Config m_config_;
};

}  // namespace cllm