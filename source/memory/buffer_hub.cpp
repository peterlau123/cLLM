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
  if (m_config_.size_levels.end() == it) {
    return;
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
    // traverse to upper levels
  }
  return block;
}

BufferHub::Size BufferHub::gradeLevel(const BufferHub::Size& sz) const {
  // TODO
}

void BufferHub::putBlock(const Block& block) {
  // TODO
}

}  // namespace cllm