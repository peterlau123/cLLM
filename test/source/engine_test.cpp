#include <gtest/gtest.h>

#include "NovaLLM/cLLM-cpp.h"

namespace nova_llm {
namespace test {

TEST(EngineTest, BasicTest) {
  Engine engine;
  EXPECT_TRUE(engine.init());
  EXPECT_TRUE(engine.isAvailable());
  EXPECT_EQ(engine.type(), DeviceType::CPU);
}

}  // namespace test
}  // namespace nova_llm