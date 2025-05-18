#pragma once

namespace cllm {

enum class DeviceType : uint32_t { UNKNOWN = 0, CPU = 0x1, GPU = 0x2, METAL = 0x4 };

}