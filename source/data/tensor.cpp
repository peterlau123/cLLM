#include "tensor.h"

#include "../utils/macros.h"

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

}  // namespace

Tensor::Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device)
    : dims_(dims), dim_sz_(dims.size()), buffer_(0), size_(0), dtype_(dtype), device_(device) {
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

  // Allocate memory for the tensor data based on the data type
  if (DeviceType::CPU == device_) {
  }

  if (DeviceType::GPU == device_) {
  }

  if (DeviceType::METAL == device_) {
    /* code */
  }
}