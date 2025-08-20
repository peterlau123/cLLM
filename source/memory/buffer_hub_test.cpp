#include "buffer_hub.h"

#if NOVA_LLM_BUILD_TESTS
#include <gtest/gtest.h>

using namespace nova_llm;

class CPUBufferHubTest : public ::testing::Test {
    public:
    const BufferHub* getBufferHub() const{
        return buffer_hub_;
    }

protected:
    void SetUp() override {
        BufferHub::Config config;
        //set config
        config.device_type = DeviceType::CPU;
        config.size_levels=std::vector<Size>{Size(0, 0, 0, 1)};
        config.alloc = std::make_shared<CPUAllocator>();

        buffer_hub_ = BufferHub::Builder::build(config);
    }

    void TearDown() override {
        BufferHub::Builder::destroy(&buffer_hub_);
    }
    BufferHub* buffer_hub_;
};

TEST(CPUBufferHubTest, Init) {
    CPUBufferHubTest test;
    auto* buffer_hub = test.getBufferHub();
    EXPECT_NE(buffer_hub, nullptr);
}

TEST(CPUBufferHubTest, GetBlock) {
    CPUBufferHubTest test;
    auto* buffer_hub = test.getBufferHub();

    auto buffer = buffer_hub->getBlock(1024);

    EXPECT_NE(buffer.data, nullptr);
    EXPECT_EQ(buffer.size, 1024);
    EXPECT_EQ(buffer.device_type, DeviceType::CPU);

    buffer_hub->put(buffer);
}

TEST(CPUBufferHubTest, PutBlock) {
    CPUBufferHubTest test;
    auto* buffer_hub = test.getBufferHub();

    auto* block = buffer_hub->getBlock(1024);

    buffer_hub->put(block);
    EXPECT_EQ(block->data, nullptr);
    EXPECT_EQ(block->size, 0);
    EXPECT_EQ(block->ref_cnt, 0);
}

TEST(CPUBufferHubTest, PutBlockFromBuffer) {
}


#endif