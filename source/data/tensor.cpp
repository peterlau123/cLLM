#include "tensor.h"

using namespace cllm;

namespace {
  // TODO: ADD OOM avoidance
  void alloc_on_cpu(Tensor::DataType dtype, int size, void** data) {
    *data = nullptr;
    switch (dtype) {
      case Tensor::DataType::INT8:
        *data = new int8_t[size];
      case Tensor::DataType::UINT8:
        *data = new uint8_t[size];
      case Tensor::DataType::INT16:
        *data = new int16_t[size];
      case Tensor::DataType::UINT16:
        *data = new uint16_t[size];
        break;
      case Tensor::DataType::INT32:
        *data = new int32_t[size];
        break;
      case Tensor::DataType::UINT32:
        *data = new uint32_t[size];
        break;
      case Tensor::DataType::FLOAT32:
        *data = new float[size];
        break;
      case Tensor::DataType::FLOAT64:
        *data = new double[size];
        break;
      case Tensor::DataType::BOOL:
        *data = new bool[size];
        break;
      default:
        throw std::invalid_argument("Unsupported data type");
    }
  }
  void dealloc_on_cpu(void** data) {
    if (*data) {
      delete[] * data;
      *data = nullptr;
    }
  }

}

Tensor::Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device)
    : dims_(dims), dim_sz_(dims.size()), data_(nullptr), size_(0), dtype_(dtype), device_(device) {
  // Check if the dimensions are valid
  if (dims.empty()) {
    throw std::invalid_argument("Tensor dimensions cannot be empty");
  }
  for (const auto& dim : dims) {
    if (dim == 0) {
      throw std::invalid_argument("Tensor dimensions cannot contain zero");
    }
  }
  // Check if the data type is valid
  if (dtype < DataType::INT8 || dtype >= DataType::TOTAL) {
    throw std::invalid_argument("Invalid data type");
  }
  // Check if the device type is valid
  if (device < DeviceType::CPU || device >= DeviceType::TOTAL) {
    throw std::invalid_argument("Invalid device type");
  }
  // Calculate the total size of the tensor
  size_ = 1;
  for (const auto& dim : dims_) {
    size_ *= dim;
  }

  // Allocate memory for the tensor data based on the data type
  if (DeviceType::CPU == device_) {
    alloc_on_cpu(dtype_, size_, &data_);
  }

  if (DeviceType::GPU == device_) {
    { /* code */ }

    if (DeviceType::METAL == device_) {
      /* code */
    }
  }