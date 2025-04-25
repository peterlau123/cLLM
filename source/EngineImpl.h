#pragma once

#include "model/model.h"

namespace cllm {

  class EngineImpl {
  public:
    EngineImpl() = default;

    bool init();
  };

}  // namespace cllm