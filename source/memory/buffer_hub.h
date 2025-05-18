#pragma once
#include "cLLM/utils/template.h"

namespace cllm {
class BufferHub {
 public:
  DEFINE_SHARED_PTR(BufferHub);

  struct Config {};

  class Builder {
   public:
    static BufferHubPtr buildSafe();

    static BufferHub* buildNative();

    static void destroy(BufferHub** hub);
  };
};


}  // namespace cllm