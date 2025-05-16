#pragma once

#include <memory>
#include <string>

namespace cllm {

class Pipeline {
 public:
  virtual ~Pipeline() = default;
  virtual std::string process(const std::string& input) = 0;
};

using PipelinePtr = std::shared_ptr<Pipeline>;

}  // namespace cllm