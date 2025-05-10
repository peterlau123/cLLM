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
  // Constructor
  Tensor() : dim_sz_(0), buffer_(nullptr), size_(0) {}

  Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device = DeviceType::CPU);

  Tensor(const Tensor& other);

  Tensor& operator=(const Tensor& other);

  // operations

  // attributes
  int dim(int idx) const;
  int size() const { return size_; }

private:
  std::vector<uint32_t> dims_;
  int dim_sz_;
  BufferPtr buffer_;
  int size_;
  // Add other tensor properties and methods as needed
  DataType dtype_;
  DeviceType device_;
};
}  // namespace cllm