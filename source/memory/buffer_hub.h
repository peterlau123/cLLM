#pragma once
#include <list>
#include <unordered_map>

#include "NovaLLM/common/device.h"
#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/utils/template.h"

namespace nova_llm {

struct Size {
  uint16_t b = 0;
  uint16_t kb = 0;
  uint16_t mb = 0;
  uint16_t gb = 0;

  [[nodiscard]] uint64_t totalBytes() const {
    return (gb << 10) * 1024 * 1024 + (mb << 10) * 1024 + (kb << 10) + b;
  }

  bool operator==(const Size& rhs) const {
    return b == rhs.b && kb == rhs.kb && mb == rhs.mb && gb == rhs.gb;
  }

  [[nodiscard]] bool isValid() const { return (b != 0 || kb != 0 || mb != 0 || gb != 0); }
};

struct SizeHash {
  std::size_t operator()(const Size& s) const { return std::hash<uint64_t>()(s.totalBytes()); }
};

struct SizeEqual {
  bool operator()(const Size& lhs, const Size& rhs) const {
    return lhs.totalBytes() == rhs.totalBytes();
  }
};

struct Block {
  using DataPtr = uint8_t*;
  using BlockPtr = Block*;
  DataPtr data = nullptr;
  BlockPtr prev = nullptr;
  BlockPtr next = nullptr;
  uint64_t size = 0;
  int32_t ref_cnt = 0;

  bool isValid() const {
    return data != nullptr && (prev != nullptr || next != nullptr) && 0 != size;
  }
};

using BlockPtr = Block::BlockPtr;

class BufferHub {
 public:
  struct Config {
    DeviceType device_type;
    std::vector<Size> size_levels;  // ensure that levels are in ascending order
    Size size_limit {0, 0, 0, 4};   // Memory in buffer hub cannot exceed this limit
    float warning_level =
        0.95;  // Be cautious when memory in buffer hub exceeds size_limit*warning_level
    IAllocatorSharedPtr allocator;
  };

  struct Level {
   public:
    BlockPtr fetchOneFreeBlock();
    void putOneBlock(const BlockPtr& block_ptr);
    uint32_t index;
    Size level_size;
    using BlockPtr = Block*;
    std::list<BlockPtr> block_list;
    using BlockIterator = std::list<BlockPtr>::iterator;
    std::unordered_map<Block::DataPtr, BlockIterator> free_map;
    std::unordered_map<Block::DataPtr, BlockIterator> busy_map;
  };

  class Builder {
   public:
    static BufferHub* build(const Config& config);

    static void destroy(BufferHub** hub);
  };

  void initConfig(const Config& config);

  BlockPtr getBlock(const Size& sz);

  void putBlock(const BlockPtr& block);

 private:
  void addSizeLevel(uint32_t index, const Size& level_sz);

  // NOTE:cautious,make sure the size level is not in use
  void eraseSizeLevel(const Size& level_sz);

  Size findNextLevel(const Size& level_sz) const;

  Size findPrevLevel(const Size& level_sz) const;

  BlockPtr coalesce(const BlockPtr& block_ptr);

  [[nodiscard]] Size gradeLevel(const Size& sz) const;

  void downSplitting(uint32_t start_level, const BlockPtr& block_ptr);

  BufferHub() = default;

  std::unordered_map<Size, Level, SizeHash, SizeEqual> buffers_;
  DeviceType device_type_;
  std::vector<Size> size_levels_;  // ensure that levels are in ascending order
  Size size_limit_ {0, 0, 0, 4};   // Memory in buffer hub cannot exceed this limit

  // Be cautious when memory in buffer hub exceeds size_limit*warning_level
  float warning_level_ = 0.95;

  IAllocatorSharedPtr allocator_;
};

}  // namespace nova_llm