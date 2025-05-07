#pragma once
#include <cstddef>

namespace cllm {
  class Buffer {
  public:
    struct DefaultDeleter {
      void operator()(void** data) {
        if (*data) {
          delete[] static_cast<char*>(*data);
          *data = nullptr;
        }
      }
    };
    using Deleter = [](void** data) {
      // Custom deleter logic if needed
    };
    Buffer() : data_(nullptr), size_(0) {}

    Buffer(size_t size) : data_(nullptr), size_(0) { resize(size); }

    Buffer(void* data, size_t size, Deleter deleter = DefaultDeleter())
        : data_(data), size_(size), deleter_(deleter) {
      if (size == 0) {
        throw std::invalid_argument("Buffer size cannot be zero");
      }
      is_extern_ = true;
    }

    ~Buffer() { dealloc(); }

    void resize(size_t size) {
      if (size != size_) {
        dealloc();
        alloc(size);
      }
    }

    void* data() const { return data_; }
    size_t size() const { return size_; }

    void clear() {
      dealloc();
      size_ = 0;
    }

    void* get() const { return data_; }
    void* get(size_t offset) const {
      if (offset >= size_) {
        throw std::out_of_range("Offset exceeds buffer size");
      }
      return static_cast<char*>(data_) + offset;
    }
    void* get(size_t offset, size_t size) const {
      if (offset + size > size_) {
        throw std::out_of_range("Offset and size exceed buffer size");
      }
      return static_cast<char*>(data_) + offset;
    }

  private:
    void* data_;
    size_t size_;
    Deleter deleter_;
    bool is_extern_;

    void alloc(size_t size) {
      data_ = new char[size];
      size_ = size;
    }

    void dealloc() {
      deleter_(data_);
      data_ = nullptr;
      size_ = 0;
    }
    Buffer(const Buffer&) = delete;             // Disable copy constructor
    Buffer& operator=(const Buffer&) = delete;  // Disable copy assignment
    Buffer(Buffer&&) = delete;                  // Disable move constructor
    Buffer& operator=(Buffer&&) = delete;       // Disable move assignment
  };
}  // namespace cllm