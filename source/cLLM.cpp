#include <fmt/format.h>

#include "EngineImpl.h"
#include "cLLM/cLLM-cpp.h"

namespace cllm {

  bool Engine::init() {
    bool ret = false;
    if (nullptr == impl_) {
      impl_ = std::make_unique<EngineImpl>();
      if (impl_->init()) {
        ret = true;
        fmt::print("Engine initialized successfully.\n");
      } else {
        fmt::print("Engine initialization failed.\n");
      }
    } else {
      fmt::print("Engine already initialized.\n");
      ret = false;
    }
    return ret;
  }

  bool Engine::parse(const std::string& modelPath) {
    // Load the model from the specified path
    // This is a placeholder implementation
    fmt::print("Loading model from: {}\n", modelPath);

    return impl_->parse(modelPath);  // Return true if loading is successful
  }

  std::string Engine::chat(const std::string& prompt) {
    // Placeholder implementation for chat functionality
    fmt::print("Chatting with prompt: {}\n", prompt);
    return impl_->chat(prompt);  // Return a dummy response
  }

}  // namespace cllm