#include "cLLM/data/tensor.h"

#include "cLLm/utils/macros.h"

using namespace cllm;

namespace {

uint64_t getByteSize(DataType dtype) {
  switch (dtype) {
    case DataType::INT8:
    case DataType::UINT8:
      return sizeof(uint8_t);
    case DataType::INT16:
    case DataType::UINT16:
      return sizeof(uint16_t);
    case DataType::INT32:
    case DataType::UINT32:
      return sizeof(uint32_t);
    case DataType::FLOAT32:
      return sizeof(float);
    case DataType::FLOAT64:
      return sizeof(double);
    case DataType::BOOL:
      return sizeof(bool);
    default:
      ASSERT(false, "Unsupported data type");
      return 0;
  }
}

}  // namespace

Tensor::Tensor() : dims_(), size_(0), m_dtype_(DataType::UNKNOWN), m_device_(DeviceType::UNKNOWN) {}

Tensor::Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device)
    : dims_(dims), size_(0), m_dtype_(dtype), m_device_(device) {
  // Check if the dimensions are valid
  ASSERT(!dims.empty(), "Tensor dimensions cannot be empty");
  for (const auto& dim : dims) {
    ASSERT(dim != 0, "Tensor dimensions cannot contain zero");
  }
  // Check if the data type is valid
  ASSERT(dtype >= DataType::INT8 && dtype < DataType::TOTAL, "Invalid data type");
  // Check if the device type is valid
  ASSERT(device >= DeviceType::CPU && device < DeviceType::TOTAL, "Invalid device type");
  // Calculate the total size of the tensor
  size_ = 1;
  for (const auto& dim : dims_) {
    size_ *= dim;
  }
  // TODO:get data
}

Tensor::Tensor(const void* data,
               const std::vector<uint32_t>& dims,
               DataType dtype,
               DeviceType device,
               Deleter deleter) {
  // TODO
}

Tensor::Tensor(const Tensor& other) {}

Tensor& Tensor::operator=(const Tensor& other) {
  Tensor ret;
  return ret;
}

Tensor& Tensor::operator*(const Tensor& rhs) {
  Tensor ret;
  return ret;
}

Tensor& Tensor::operator+(const Tensor& rhs) {
  Tensor ret;
  return ret;
}

Tensor::~Tensor() {}
