#include "buffer_hub.h"

#include <algorithm>

#include "NovaLLM/utils/log.h"

namespace nova_llm {

BufferHub* BufferHub::Builder::build(const Config& config) {
  BufferHub* hub = new BufferHub;
  hub->initConfig(config);
  int index = 0;
  for (auto v : config.size_levels) {
    hub->addSizeLevel(index, v);
    ++index;
  }
  // TODO:other
  return hub;
}

void BufferHub::Builder::destroy(nova_llm::BufferHub** hub) {
  // TODO:destroy whole hub
}

void BufferHub::initConfig(const Config& config) {
  device_type_ = config.device_type;
  size_levels_ = config.size_levels;
  // sort size levels in ascending order
  std::sort(size_levels_.begin(), size_levels_.end(), [](const Size& a, const Size& b) {
    return a.totalBytes() < b.totalBytes();
  });
  size_limit_ = config.size_limit;
  warning_level_ = config.warning_level;
  allocator_ = config.allocator;
}

void BufferHub::addSizeLevel(uint32_t index, const Size& level_sz) {
  auto& level = buffers_[level_sz];
  level.level_size = level_sz;
  level.index = index;
}

void BufferHub::eraseSizeLevel(const Size& level_sz) {
  if (buffers_.count(level_sz)) {
    if (buffers_[level_sz].busy_map.empty()) {
      // TODO:destroy this level
    }
  } else {
    LOG_WARN("Level with size %d is not found!", level_sz.totalBytes());  // TODO:optimize
  }
}

BufferHub::Size BufferHub::findNextLevel(const Size& level_sz) const {
  if (buffers_.count(level_sz)) {
    auto level_index = buffers_.at(level_sz).index;
    if (++level_index < size_levels_.size()) {
      return size_levels_[++level_index];
    }
  }
  LOG_WARN("No next level found");
  return Size {};
}

BufferHub::Size BufferHub::findPrevLevel(const Size& level_sz) const {
  if (buffers_.count(level_sz)) {
    auto level_index = buffers_.at(level_sz).index;
    if (--level_index >= 0) {
      return size_levels_[--level_index];
    }
  }
  return Size {};
}

void BufferHub::coalesce() {}

Block BufferHub::getBlock(const Size& sz) {
  // round it to ceil level
  auto level_sz = gradeLevel(sz);
  // search the block list
  Block ret_block;
  if (buffers_.count(level_sz)) {
    auto& level = buffers_[level_sz];
    Block block = level.fetchOneFreeBlock();
    if (block.isValid()) {
      return block;
    }
    // traverse to upper levels
    auto next_sz = findNextLevel(level_sz);
    while (next_sz.isValid()) {
      level = buffers_[level_sz];
      block = level.fetchOneFreeBlock();
      if (block.isValid()) {
        ret_block = block;
        break;
      } else {
        next_sz = findNextLevel(next_sz);
      }
    }
    if (!ret_block.isValid()) {  // NOTE:向upper level中也都没找到空闲的block
      auto top_level_size = *(size_levels_.rbegin());
      uint16_t total_bytes = top_level_size.totalBytes();
      void* data = allocator_->allocate(total_bytes);
      Block new_block {};
      new_block.data = reinterpret_cast<uint8_t*>(data);
      new_block.prev = nullptr;
      new_block.next = nullptr;
      new_block.size = total_bytes;

      const auto& top_level = buffers_[top_level_size];
      this->downSplitting(top_level.index - 1, block);
    }
  } else {
    LOG_WARN("Unable to find available block of size %d", sz.totalBytes());
  }
  return ret_block;
}

void BufferHub::putBlock(const Block& block) {
  // TODO
}

BufferHub::Size BufferHub::gradeLevel(const BufferHub::Size& sz) const {
  // TODO
}

void BufferHub::downSplitting(uint32_t start_level, const nova_llm::Block& block) {
  auto block_size = block.size;
  uint8_t* data_addr = block.data;
  uint32_t cur_level = start_level;

  while (size_levels_[cur_level].totalBytes() < block_size) {
    auto sz = size_levels_[cur_level];
    auto& level = buffers_[sz];
    Block b {data_addr, nullptr, nullptr, sz.totalBytes(), 0};
    level.putOneBlock(b);

    data_addr += sz.totalBytes();
    block_size -= sz.totalBytes();
    cur_level--;
  }
}

}  // namespace nova_llm