#include "buffer.h"

#include "../utils/macros.h"
#include "allocator.h"

namespace cllm {

  void Buffer::alloc(size_t size) {
    data_ = allocator_->alloc(size);
    if (data_ == nullptr) {
      throw std::bad_alloc();
    }
    size_ = size;
  }

  void Buffer::dealloc() {
    deletor_(data_);
    data_ = nullptr;
    size_ = 0;
  }

  Buffer::Buffer(size_t size) : data_(nullptr), size_(0) {
    ASSERT(0 < size_, "Buffer size cannot be zero");
    resize(size);
  }

  Buffer::Buffer(void* data, size_t size, Deletor deleter)
      : data_(data), size_(size), deletor_(deleter) {
    ASSERT(0 < size_, "Buffer size cannot be zero");
    is_extern_ = true;
  }

  Buffer::~Buffer() { dealloc(); }

  void Buffer::resize(size_t size) {
    if (size != size_) {
      dealloc();
      alloc(size);
    }
  }

  void* Buffer::data() const { return data_; }
  size_t Buffer::size() const { return size_; }

  void Buffer::clear() {
    dealloc();
    size_ = 0;
  }

  void* Buffer::get() const { return data_; }
  void* Buffer::get(size_t offset) const {
    ASSERT(size_ < offset, "offset cannot exceed Buffer size");
    return static_cast<char*>(data_) + offset;
  }
  void* Buffer::get(size_t offset, size_t size) const {
    ASSERT(size_ < offset, "offset and size cannot exceed Buffer size");

    return static_cast<char*>(data_) + offset;
  }

}  // namespace cllm