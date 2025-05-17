#include <fmt/format.h>

#include "EngineImpl.h"
#include "cLLM/cLLM-cpp.h"

namespace cllm {

class Impl {
 public:
  [[nodiscard]] static Impl* build() {
    auto ptr = new Impl;
    return ptr;
  }

  static void destroy(Impl** ptr) {
    if (*ptr) {
      delete *ptr;
      *ptr = nullptr;
    }
  }

  EngineImplPtr engine_ptr;
};

Engine::Engine() { impl_ = Impl::build(); }

Engine::~Engine() { Impl::destroy(&impl_); }

bool Engine::init() {
  bool ret = false;
  if (nullptr == impl_) {
    impl_->engine_ptr = EngineImpl::build();
    if (impl_->engine_ptr->init()) {
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

  return impl_->engine_ptr->parse(modelPath);  // Return true if loading is successful
}

std::string Engine::chat(const std::string& prompt) {
  // Placeholder implementation for chat functionality
  fmt::print("Chatting with prompt: {}\n", prompt);
  return impl_->engine_ptr->chat(prompt);  // Return a dummy response
}

}  // namespace cllm