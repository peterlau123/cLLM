#include "buffer.h"

#include "../utils/macros.h"
#include "allocator.h"

namespace cllm {

Buffer::Buffer(DeviceType device_type)
    : device_type_(device_type), data_(nullptr), size_(0), is_extern_(false) {
  allocator_ = std::make_shared<CPUAllocator>();
  deletor_ = DefaultDeleter();
}

void Buffer::alloc(size_t size) {
  allocator_->alloc(size, &data_);
  if (data_ == nullptr) {
    throw std::bad_alloc();
  }
  size_ = size;
}

void Buffer::dealloc() {
  deletor_(&data_);
  data_ = nullptr;
  size_ = 0;
}

Buffer::Buffer(DeviceType device_type, size_t size)
    : device_type_(device_type), data_(nullptr), size_(0) {
  ASSERT(0 < size_, "Buffer size cannot be zero");
  resize(size);
}

Buffer::Buffer(DeviceType device_type, void* data, size_t size, Deletor deleter)
    : device_type_(device_type), data_(data), size_(size), deletor_(deleter) {
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