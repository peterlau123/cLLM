#pragma once
#include <list>
#include <unordered_map>

#include "NovaLLM/common/device.h"
#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/utils/template.h"

namespace nova_llm {
struct Block {
  using DataPtr = uint8_t*;
  DataPtr data = nullptr;
  DataPtr prev = nullptr;
  DataPtr next = nullptr;
  uint64_t size = 0;
  int32_t ref_cnt = 0;

  bool isValid() const {
    return data != nullptr && (prev != nullptr || next != nullptr) && 0 != size;
  }
};

class BufferHub {
 public:
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
    Block fetchOneFreeBlock() {
      if (!free_map.empty()) {
        auto it = free_map.begin();
        auto block_it = it->second;
        block_it->ref_cnt++;
        busy_map.insert({it->first, it->second});
        free_map.erase(it);
        return *(block_it);
      }
      return Block {};
    }

    // TODO
    void putOneBlock(const Block& block) {
      Block dst_block(block);
      if (!block_list.empty()) {
        auto it = block_list.rbegin();
        dst_block.prev = it->data;
      }
      auto ret_it = block_list.insert(block_list.end(), dst_block);
      if (0 == free_map.count(dst_block.data)) {
        free_map.insert({dst_block.data, ret_it});
      }
    }

    uint32_t index;
    Size level_size;
    std::list<Block> block_list;
    using BlockIterator = std::list<Block>::iterator;
    std::unordered_map<Block::DataPtr, BlockIterator> free_map;
    std::unordered_map<Block::DataPtr, BlockIterator> busy_map;
  };

  class Builder {
   public:
    static BufferHub* build(const Config& config);

    static void destroy(BufferHub** hub);
  };

  void initConfig(const Config& config);

  Block getBlock(const Size& sz);

  void putBlock(const Block& block);

 private:
  void addSizeLevel(uint32_t index, const Size& level_sz);

  // NOTE:cautious,make sure the size level is not in use
  void eraseSizeLevel(const Size& level_sz);

  Size findNextLevel(const Size& level_sz) const;

  Size findPrevLevel(const Size& level_sz) const;

  void coalesce();

  [[nodiscard]] Size gradeLevel(const Size& sz) const;

  void downSplitting(uint32_t start_level, const Block& block);

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