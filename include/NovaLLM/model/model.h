#pragma once

#include "NovaLLM/utils/macros.h"

namespace nova_llm {

class NOVA_LLM_API Model {
 public:
  Model() = default;
  virtual ~Model() = default;

  virtual bool init() = 0;
  virtual bool load(const std::string& path) = 0;
  virtual bool unload() = 0;
};

using ModelPtr = std::shared_ptr<Model>;

}  // namespace nova_llm