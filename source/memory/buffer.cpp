#include "buffer.h"

namespace cllm {

  Buffer::Buffer(size_t size) : data_(nullptr), size_(0) { resize(size); }

  Buffer::Buffer(void* data, size_t size, Deleter deleter)
      : data_(data), size_(size), deleter_(deleter) {
    if (size == 0) {
      throw std::invalid_argument("Buffer size cannot be zero");
    }
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
    if (offset >= size_) {
      throw std::out_of_range("Offset exceeds buffer size");
    }
    return static_cast<char*>(data_) + offset;
  }
  void* Buffer::get(size_t offset, size_t size) const {
    if (offset + size > size_) {
      throw std::out_of_range("Offset and size exceed buffer size");
    }
    return static_cast<char*>(data_) + offset;
  }

}  // namespace cllm