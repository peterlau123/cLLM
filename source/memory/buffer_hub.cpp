#include "buffer_hub.h"

#include <spdlog/spdlog.h>

#include <algorithm>

#include "cLLM/memory/allocator.h"

namespace cllm {

BufferHub* BufferHub::Builder::build(const Config& config) {
  BufferHub* hub = new BufferHub;
  hub->setConfig(config);
  for (auto v : config.size_levels) {
    hub->addSizeLevel(v);
  }
  // TODO:other
  return hub;
}

void BufferHub::Builder::destroy(cllm::BufferHub** hub) {
  // TODO:destroy whole hub
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
    // TODO:do destroy for each block
  }
}

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
    // traverse to upper or lower levels
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


}  // namespace cllm