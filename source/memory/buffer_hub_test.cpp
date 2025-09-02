#include "buffer_hub.h"

#if EnableModuleTest
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
        config.allocator = std::make_shared<CPUAllocator>();

        buffer_hub_ = BufferHub::Builder::build(config);
    }

    void TearDown() override {
        BufferHub::Builder::destroy(&buffer_hub_);
    }
    BufferHub* buffer_hub_;
};

TEST_F(CPUBufferHubTest, Init) {
    EXPECT_NE(getBufferHub(), nullptr);
}

TEST_F(CPUBufferHubTest, GetBlock) {
    auto buffer = getBufferHub()->getBlock(1024);

    EXPECT_NE(buffer.data, nullptr);
    EXPECT_EQ(buffer.size, 1024);
    EXPECT_EQ(buffer.device_type, DeviceType::CPU);

    getBufferHub()->put(buffer);
}

TEST_F(CPUBufferHubTest, PutBlock) {
    auto* block = getBufferHub()->getBlock(1024);

    EXPECT_NE(block, nullptr);
    EXPECT_EQ(block->data, nullptr);
    EXPECT_EQ(block->size, 0);
    EXPECT_EQ(block->ref_cnt, 0);

    getBufferHub()->put(block);
}


TEST_F(CPUBufferHubTest, PutBlockFromBuffer) {
    auto* buffer = getBufferHub()->getBlock(1024);

    EXPECT_NE(buffer, nullptr);
    EXPECT_EQ(buffer->data, nullptr);
    EXPECT_EQ(buffer->totalElements(), 0);
    EXPECT_EQ(buffer->ref_cnt, 0);

    getBufferHub()->putBlockFromBuffer(buffer);
}

#endif