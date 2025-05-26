#include "NovaLLM/memory/allocator.h"

namespace nova_llm {


CPUAllocator::CPUAllocator() {}

CPUAllocator::~CPUAllocator() {}

void *CPUAllocator::do_allocate(size_t size) {}

void CPUAllocator::do_deallocate(void *ptr) {}

}  // namespace nova_llm