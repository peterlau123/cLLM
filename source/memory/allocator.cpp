#include "allocator.h"

#include <new>

namespace cllm {

CPUAllocator::CPUAllocator() {
  // Constructor implementation
}

CPUAllocator::~CPUAllocator() {
  // Destructor implementation
}

void CPUAllocator::alloc(int size, void** data) {
  *data = new char[size];
  if (*data == nullptr) {
    throw std::bad_alloc();
  }
}

void CPUAllocator::dealloc(void** data) {
  if (*data) {
    delete[] static_cast<char*>(*data);
    *data = nullptr;
  }
}
}  // namespace cllm