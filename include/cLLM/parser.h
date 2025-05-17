#pragma once

#include <memory>
#include <string>

namespace cllm {

class Parser {
 public:
  virtual ~Parser() = default;
  virtual bool parse(const std::string& modelPath) = 0;
};

using ParserPtr = std::shared_ptr<Parser>;

}  // namespace cllm