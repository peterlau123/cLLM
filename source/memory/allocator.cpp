#include "NovaLLM/memory/allocator.h"

namespace nova_llm {

void* Allocator::allocate(size_t size) { return nullptr; }

void Allocator::deallocate(void* ptr) {}

bool Allocator::isAvailable() const { return true; }

}  // namespace nova_llm