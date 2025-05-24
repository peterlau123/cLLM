#include "NovaLLM/memory/allocator.h"

namespace nova_llm {


CPUAllocator::CPUAllocator() {}

CPUAllocator::~CPUAllocator() {}

void *CPUAllocator::do_allocate(size_t size) {}

}  // namespace nova_llm