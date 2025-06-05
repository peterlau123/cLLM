#include "NovaLLM/memory/allocator.h"

namespace nova_llm {


CPUAllocator::CPUAllocator() {}

CPUAllocator::~CPUAllocator() {}

void *CPUAllocator::do_allocate(size_t size) { return malloc(size); }

void CPUAllocator::do_deallocate(void *ptr) {
  if (ptr) {
    free(ptr);
  }
}


}  // namespace nova_llm