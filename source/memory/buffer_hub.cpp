#include "buffer_hub.h"

#include <algorithm>

#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/utils/log.h"

namespace nova_llm {

BufferHub* BufferHub::Builder::build(const Config& config) {
  BufferHub* hub = new BufferHub;
  hub->initConfig(config);

  for (auto v : config.size_levels) {
    hub->addSizeLevel(v);
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
  size_limit_ = config.size_limit;
  warning_level_ = config.warning_level;
  allocator_ = config.allocator;
}

void BufferHub::addSizeLevel(const Size& level_sz) {
  auto& level = buffers_[level_sz];
  level.level_size = level_sz;
}

void BufferHub::eraseSizeLevel(const Size& level_sz) {
  if (buffers_.count(level_sz)) {
    if (buffers_[level_sz].busy_map.empty()) {
      // TODO:destroy this level
    }
  } else {
    LOG_WARN("Level %d is not found!", level_sz.level);
  }
}

BufferHub::Size BufferHub::findNextLevel(const Size& level_sz) const {
  int level = level_sz.level;
  if (level <= size_levels_.size() - 1) {
    return size_levels_[level + 1];
  }
  LOG_WARN("No next level found");
  return Size {};
}

BufferHub::Size BufferHub::findPrevLevel(const Size& level_sz) const {
  int level = level_sz.level;
  if (--level < 0) {
    LOG_WARN("No prev level found!");
    return Size {};
  }
  return size_levels_[--level];
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
      uint16_t total_bytes = size_levels_.rbegin()->totalBytes();
      void* data = allocator_->allocate(total_bytes);
      Block new_block {};
      new_block.data = reinterpret_cast<uint8_t*>(data);
      new_block.prev = nullptr;
      new_block.next = nullptr;
      new_block.size = total_bytes;
      // TODO: downsplitting
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


}  // namespace nova_llm