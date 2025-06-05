#include <fmt/format.h>

#include "NovaLLM/NovaLLM-cpp.h"
#include "NovaLLM/utils/log.h"
#include "engine/EngineImpl.h"

namespace nova_llm {

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

bool Engine::init() {
  // Implementation
  return true;
}

void Engine::run() {}

Engine::~Engine() { Impl::destroy(&impl_); }

}  // namespace nova_llm