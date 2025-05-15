#pragma once
#include <cstdint>
#include <vector>

#include "../memory/buffer.h"

namespace cllm {

/**
 * @brief 张量类，用于表示和操作多维数组数据
 *
 * @details 支持多种数据类型(如INT8、FLOAT32等)和设备类型(CPU/GPU)，
 *          提供基本的张量运算操作，包括乘法和加法。
 */
class Tensor {
 public:
  /**
   * @brief 数据类型枚举
   */
  enum class DataType {
    UNKNOWN = -1,  ///< 未知类型
    INT8,          ///< 8位整数
    UINT8,         ///< 8位无符号整数
    INT16,         ///< 16位整数
    UINT16,        ///< 16位无符号整数
    INT32,         ///< 32位整数
    UINT32,        ///< 32位无符号整数
    FLOAT32,       ///< 32位浮点数
    FLOAT64,       ///< 64位浮点数
    BOOL,          ///< 布尔类型
    TOTAL          ///< 类型总数
  };

  /**
   * @brief 默认删除器
   */
  struct DefaultDeletor {
    void operator()(void** data) {}
  };

  using Deleter = std::function<void(void**)>;

  /**
   * @brief 默认构造函数
   */
  Tensor();

  /**
   * @brief 构造指定维度和类型的张量
   *
   * @param dims 张量的维度数组
   * @param dtype 数据类型
   * @param device 设备类型，默认为CPU
   */
  Tensor(const std::vector<uint32_t>& dims, DataType dtype, DeviceType device = DeviceType::CPU);

  /**
   * @brief 从现有数据构造张量
   *
   * @param data 指向数据的指针
   * @param dims 张量的维度数组
   * @param dtype 数据类型
   * @param device 设备类型
   * @param deleter 自定义删除器，默认使用DefaultDeletor
   */
  Tensor(const void* data,
         const std::vector<uint32_t>& dims,
         DataType dtype,
         DeviceType device,
         Deleter deleter = DefaultDeletor());

  /**
   * @brief 从Buffer构造张量
   *
   * @param buffer_ptr 指向Buffer的智能指针
   */
  Tensor(const BufferPtr& buffer_ptr);

  /**
   * @brief 拷贝构造函数
   *
   * @param other 要拷贝的张量
   */
  Tensor(const Tensor& other);

  /**
   * @brief 赋值运算符
   *
   * @param other 要赋值的张量
   * @return Tensor& 返回自身引用
   */
  Tensor& operator=(const Tensor& other);

  /**
   * @brief 张量乘法运算
   *
   * @param rhs 右操作数
   * @return Tensor& 返回结果张量的引用
   */
  Tensor& operator*(const Tensor& rhs);

  /**
   * @brief 张量加法运算
   *
   * @param rhs 右操作数
   * @return Tensor& 返回结果张量的引用
   */
  Tensor& operator+(const Tensor& rhs);

  vector<uint32_t> dims() const { return dims_; }

  /**
   * @brief 获取指定维度的大小
   *
   * @param idx 维度索引
   * @return int 返回该维度的大小
   */
  uint32_t dimAt(uint32_t idx) const {
    if (static_cast<int>(dims_.size()) <= idx) {
      return -1;  // TODO: 异常处理
    }
    return dims_[idx];
  }

  /**
   * @brief 获取张量的元素总数
   *
   * @return int 元素总数
   */
  int size() const { return size_; }

  /**
   * @brief 析构函数
   */
  ~Tensor();

 private:
  std::vector<uint32_t> dims_;  ///< 张量的维度数组
  int size_;                    ///< 元素总数
  BufferPtr buffer_;            ///< 数据缓冲区
  DataType dtype_;              ///< 数据类型
  DeviceType device_;           ///< 设备类型
  int ref_count_;               ///< 引用计数
};

}  // namespace cllm