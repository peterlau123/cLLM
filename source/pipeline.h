#pragma once
#include <memory>

#include "model.h"
#include "tokenizer.h"

namespace cllm {

  class Pipeline {};
  using PipelinePtr = std::shared_ptr<Pipeline>;

  class Qwenpipeline : public Pipeline {};

}  // namespace cllm