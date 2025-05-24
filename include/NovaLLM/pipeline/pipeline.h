#pragma once
#include "../../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.1.sdk/usr/include/c++/v1/memory"
#include "../decode/decoder.h"
#include "../encode/encoder.h"
#include "../model/model.h"
#include "../utils/macros.h"
#include "tokenizer.h"

namespace nova_llm {

class NOVA_LLM_API Pipeline {
 public:
  Pipeline();

  virtual ~Pipeline();

  bool init();
  bool process(const std::string& input, std::string& output);

  // Add methods for pipeline processing
  virtual void process() = 0;

 private:
  std::unique_ptr<Decoder> decoder_;
  std::unique_ptr<Encoder> encoder_;
};
DEFINE_SHARED_PTR(Pipeline);

class Qwenpipeline : public Pipeline {
 public:
  Qwenpipeline() ;

  ~Qwenpipeline() override;

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