#include "buffer_hub.h"

#include <algorithm>

#include "NovaLLM/memory/allocator.h"
#include "NovaLLM/utils/log.h"

namespace nova_llm {

BufferHub* BufferHub::Builder::build(const Config& config) {
  BufferHub* hub = new BufferHub;
  hub->setConfig(config);
  for (auto v : config.size_levels) {
    hub->addSizeLevel(v);
  }
  // TODO:other
  return hub;
}

void BufferHub::Builder::destroy(nova_llm::BufferHub** hub) {
  // TODO:destroy whole hub
}

void BufferHub::setConfig(const Config& config) {
  m_config_ = config;
  // TODO: ensure that the config values are valid
}

void BufferHub::addSizeLevel(const Size& level_sz) {
  uint64_t total_bytes = level_sz.totalBytes();
  auto it =
      std::find_if(m_config_.size_levels.begin(),
                   m_config_.size_levels.end(),
                   [&](const auto& item) { return level_sz.totalBytes() == item.totalBytes(); });
  if (m_config_.size_levels.end() != it) {
    buffers_[level_sz] = std::list<Block>();
  }
}

void BufferHub::eraseSizeLevel(const Size& level_sz) {
  if (0 != buffers_.count(level_sz)) {
    auto& block_list = buffers_[level_sz];
    // TODO:do destroy for each block, can only be destroyed when any block is not referenced
  }
}

BufferHub::Size BufferHub::findNextLevel(const Size& level_sz) const {
  int level = level_sz.level;
  if (level <= m_config_.size_levels.size() - 1) {
    return m_config_.size_levels[level + 1];
  }
  LOG_WARN("No next level found");
  return Size();
}

BufferHub::Size BufferHub::findPrevLevel(const Size& lavel_sz) const {}

void BufferHub::coalesce() {}

Block BufferHub::getBlock(const Size& sz) {
  // round it to ceil level
  auto level_sz = gradeLevel(sz);
  // search the block list
  Block block;
  if (buffers_.count(level_sz)) {
    auto& block_list = buffers_[level_sz];
    for (auto& b : block_list) {
      if (0 == b.ref_cnt) {
        b.ref_cnt++;
        return b;
      }
    }
    // traverse to upper levels
    auto next_sz = findNextLevel(level_sz);
    if (next_sz.isValid()) {  // find next level
      // check whether next level has enough space
    } else {
      // TODO:allocate new block
    }
    // For upper levels, we need to split
    // For lower levels, we need to coalesce
  }
  return block;
}

void BufferHub::putBlock(const Block& block) {
  // TODO
}

BufferHub::Size BufferHub::gradeLevel(const BufferHub::Size& sz) const {
  // TODO
}


}  // namespace nova_llm