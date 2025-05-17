#include <cLLM/cLLM-cpp.h>
#include <gtest/gtest.h>

using namespace cllm;

class EngineTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup code that will be called before each test
  }

  void TearDown() override {
    // Cleanup code that will be called after each test
  }
};

TEST_F(EngineTest, InitializationTest) {
  Engine engine;
  EXPECT_TRUE(engine.init());
}

TEST_F(EngineTest, ParseModelTest) {
  Engine engine;
  ASSERT_TRUE(engine.init());
  EXPECT_TRUE(engine.parse("path/to/model"));
}

TEST_F(EngineTest, ChatTest) {
  Engine engine;
  ASSERT_TRUE(engine.init());
  ASSERT_TRUE(engine.parse("path/to/model"));

  std::string response = engine.chat("Hello");
  EXPECT_FALSE(response.empty());
}

TEST_F(EngineTest, InvalidModelPathTest) {
  Engine engine;
  ASSERT_TRUE(engine.init());
  EXPECT_FALSE(engine.parse("invalid/path/to/model"));
}