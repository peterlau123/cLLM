#pragma once
#include <cstddef>
#include <functional>

#include "../backend/device.h"

namespace cllm {
  class Allocator;
  using AllocatorPtr = std::shared_ptr<Allocator>;
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
    using Deletor = std::function<void(void**)>;

    Buffer(DeviceType device_type);

    Buffer(DeviceType device_type, size_t size);

    Buffer(DeviceType device_type, void* data, size_t size, Deletor deletor = DefaultDeleter());

    ~Buffer();

    void reserve(size_t size);

    void resize(size_t size);

    void* data() const;

    size_t size() const;

    void clear();

    void* get() const;

    void* get(size_t offset) const;

    void* get(size_t offset, size_t size) const;

  private:
    DeviceType device_type_;
    void* data_;
    size_t size_;  // in bytes
    Deletor deletor_;
    bool is_extern_;
    AllocatorPtr allocator_;
    void alloc(size_t size);

    void dealloc();

    Buffer(const Buffer&) = delete;             // Disable copy constructor
    Buffer& operator=(const Buffer&) = delete;  // Disable copy assignment
    Buffer(Buffer&&) = delete;                  // Disable move constructor
    Buffer& operator=(Buffer&&) = delete;       // Disable move assignment
  };
}  // namespace cllm