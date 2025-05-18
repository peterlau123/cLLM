#include "buffer_hub.h"

namespace cllm {


BufferHub::BufferHubPtr BufferHub::Builder::buildSafe() { return nullptr; }

BufferHub* BufferHub::Builder::buildNative() { return nullptr; }

void BufferHub::Builder::destroy(cllm::BufferHub** hub) {}


}  // namespace cllm