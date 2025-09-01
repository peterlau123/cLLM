#include <gtest/gtest.h>

#include "NovaLLM/NovaLLM-cpp.h"

namespace nova_llm {
namespace test {

TEST(EngineTest, BasicTest) {
  Engine engine;
  EXPECT_TRUE(engine.init());
}

}  // namespace test
}  // namespace nova_llm