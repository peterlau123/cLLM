#include "NovaLLM/data/tensor.h"

#include "NovaLLM/memory/buffer_manager.h"
#include "NovaLLM/utils/macros.h"

namespace nova_llm {

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

Tensor::Tensor()
    : dims_(), ele_cnt_(0), m_dtype_(DataType::UNKNOWN), m_device_(DeviceType::UNKNOWN) {}

Tensor::Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device)
    : dims_(dims), ele_cnt_(0), m_dtype_(dtype), m_device_(device) {
  // Check if the dimensions are valid
  ASSERT(!dims.empty(), "Tensor dimensions cannot be empty");
  for (const auto& dim : dims) {
    ASSERT(dim != 0, "Tensor dimensions cannot contain zero");
  }
  // Check if the data type is valid
  ASSERT(dtype >= DataType::INT8 && dtype < DataType::TOTAL, "Invalid data type");
  // Check if the device type is valid
  ASSERT(device >= DeviceType::CPU && device <= DeviceType::METAL, "Invalid device type");
  // Calculate the total elements of the tensor
  ele_cnt_ = 1;
  for (const auto& dim : dims_) {
    ele_cnt_ *= dim;
  }
  Buffer buffer =
      BufferManager::Builder::getInstance().fetch(ele_cnt_ * sizeof(m_dtype_), m_device_);
  this->data_ = buffer.data;
  this->data_size_ = buffer.size;
  m_deleter_ = [&](void** data) {
    BufferManager::Builder::getInstance().put(Buffer(*data, data_size_, m_device_));
    *data = nullptr;
  };
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

Tensor::~Tensor() {
  if (0 == --ref_count_) {
    m_deleter_(&data_);
  }
}

}  // namespace nova_llm
