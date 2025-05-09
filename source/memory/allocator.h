#pragma once

namespace cllm {
  class Allocator {
  public:
    Allocator() = default;
    virtual ~Allocator() = default;

    /*
     * @brief Allocates memory of the given size.
     * @param size Size of the memory to allocate in bytes.
     * @param data Pointer to the allocated memory.
     */
    virtual void alloc(int size, void** data) = 0;
    virtual void dealloc(void** data) = 0;
  };

  class CPUAllocator : public Allocator {
  public:
    void alloc(int size, void** data) override;
    void dealloc(void** data) override;
  };
}  // namespace cllm