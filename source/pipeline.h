#pragma once
#include <memory>

#include "model/model.h"
#include "tokenizer.h"

namespace cllm {

class Pipeline {
public:
  Pipeline() = default;

  virtual ~Pipeline() = default;

  // Add methods for pipeline processing
  virtual void process() = 0;
};
using PipelinePtr = std::shared_ptr<Pipeline>;

class Qwenpipeline : public Pipeline {
public:
  Qwenpipeline() = default;

  ~Qwenpipeline() override = default;

  void process() override {
    // Implement the processing logic for Qwen pipeline
  }

private:
  QwenModelPtr qwen_model_;
  Tokenizer tokenizer_;
};

template <typename T>
PipelinePtr createPipeline() {
  return std::make_shared<T>();
}

}  // namespace cllm