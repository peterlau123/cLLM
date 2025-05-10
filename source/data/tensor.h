#pragma once
#include <cstdint>
#include <vector>

#include "../memory/buffer.h"  // Assuming Buffer is defined in this header

namespace cllm {
class Tensor {
 public:
  enum class DataType {
    UNKNOWN = -1,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    FLOAT32,
    FLOAT64,
    BOOL,
    TOTAL
  };

  struct DefaultDeletor {
    void operator()(void** data) {}
  };

  using Deleter = std::function<void(void**)>;
  // Constructor
  Tensor();

  Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device = DeviceType::CPU);

  Tensor(const void* data,
         const std::vector<uint32_t>& dims,
         DataType dtype,
         DeviceType device,
         Deleter deleter = DefaultDeletor());

  Tensor(const BufferPtr& buffer_ptr);

  Tensor(const Tensor& other);

  Tensor& operator=(const Tensor& other);


  // operations
  Tensor& operator*(const Tensor& rhs);

  Tensor& operator+(const Tensor& rhs);

  // attributes
  int dim(int idx) const;

  int size() const { return size_; }

  ~Tensor();

 private:
  std::vector<uint32_t> dims_;
  int size_;  // element number
  BufferPtr buffer_;
  DataType dtype_;
  DeviceType device_;

  int ref_count_;  // TODO: add ref count
};
}  // namespace cllm