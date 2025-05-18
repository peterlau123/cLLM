#pragma once
#include "../utils/template.h"

namespace cllm {

class QwenModel {};
DEFINE_SHARED_PTR(QwenModel);

class DeepSeekModel {};
DEFINE_SHARED_PTR(DeepSeekModel);

class LlamaModel {};
DEFINE_SHARED_PTR(LlamaModel);


}  // namespace cllm