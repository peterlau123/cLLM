#pragma once
#include <memory>

#include "NovaLLM/decode/decoder.h"
#include "NovaLLM/encode/encoder.h"
#include "NovaLLM/utils/macros.h"
#include "model/model.h"
#include "tokenizer.h"

namespace nova_llm {

class NOVA_LLM_API Pipeline {
 public:
  Pipeline();

  ~Pipeline();

  bool init();
  bool process(const std::string& input, std::string& output);

  // Add methods for pipeline processing
  virtual void process() = 0;

 private:
  std::unique_ptr<Decoder> decoder_;
  std::unique_ptr<Encoder> encoder_;
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

}  // namespace nova_llm