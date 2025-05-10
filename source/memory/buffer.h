#pragma once
#include <cstddef>
#include <functional>

#include "../backend/device.h"
#include "allocator.h"

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
  using Deletor = std::function<void(void**)>;
  using BufferPtr = std::shared_ptr<Buffer>;

  class Builder {
  public:
    static BufferPtr build(DeviceType device_type) { return std::make_shared<Buffer>(device_type); }
    static BufferPtr build(DeviceType device_type, size_t size) {
      return std::make_shared<Buffer>(device_type, size);
    }
    static BufferPtr build(DeviceType device_type,
                           void* data,
                           size_t size,
                           Deletor deletor = DefaultDeleter()) {
      return std::make_shared<Buffer>(device_type, data, size, deletor);
    }
  };

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
  Buffer(DeviceType device_type);

  Buffer(DeviceType device_type, size_t size);

  Buffer(DeviceType device_type, void* data, size_t size, Deletor deletor = DefaultDeleter());

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
using BufferPtr = Buffer::BufferPtr;
}  // namespace cllm