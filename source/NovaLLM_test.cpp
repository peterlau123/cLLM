#include <gtest/gtest.h>

#include "NovaLLM/NovaLLM-cpp.h"

using namespace nova_llm;

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
  auto engine = std::make_unique<Engine>();
  EXPECT_TRUE(engine->init());
}

// Test model parsing
TEST_F(EngineImplTest, ParseModelTest) {
  auto engine = std::make_unique<Engine>();
  EXPECT_TRUE(engine->init());
  EXPECT_TRUE(engine->parse("test_model.bin"));
}

// Test chat functionality
TEST_F(EngineImplTest, ChatTest) {
  auto engine = std::make_unique<Engine>();
  EXPECT_TRUE(engine->init());
  EXPECT_TRUE(engine->parse("test_model.bin"));

  std::string response = engine->chat("Hello");
  EXPECT_FALSE(response.empty());
}

// Test invalid model path
TEST_F(EngineImplTest, InvalidModelPathTest) {
  auto engine = std::make_unique<Engine>();
  EXPECT_TRUE(engine->init());
  EXPECT_FALSE(engine->parse("invalid/path/to/model"));
}

// Main function to run all tests
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}