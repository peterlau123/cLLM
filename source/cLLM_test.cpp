#include <gtest/gtest.h>

#include "EngineImpl.h"
#include "cLLM/cLLM-cpp.h"

using namespace cllm;

// Test fixture for EngineImpl
class EngineImplTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup code that will be called before each test
  }

  void TearDown() override {
    // Cleanup code that will be called after each test
  }
};

// Test initialization
TEST_F(EngineImplTest, InitializationTest) {
  EngineImpl engine;
  EXPECT_TRUE(engine.init());
}

// Test model parsing
TEST_F(EngineImplTest, ParseModelTest) {
  EngineImpl engine;
  ASSERT_TRUE(engine.init());
  EXPECT_TRUE(engine.parse("path/to/model"));
}

// Test chat functionality
TEST_F(EngineImplTest, ChatTest) {
  EngineImpl engine;
  ASSERT_TRUE(engine.init());
  ASSERT_TRUE(engine.parse("path/to/model"));

  std::string response = engine.chat("Hello");
  EXPECT_FALSE(response.empty());
}

// Test invalid model path
TEST_F(EngineImplTest, InvalidModelPathTest) {
  EngineImpl engine;
  ASSERT_TRUE(engine.init());
  EXPECT_FALSE(engine.parse("invalid/path/to/model"));
}

// Main function to run all tests
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}