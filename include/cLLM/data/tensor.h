#pragma once


class Tensor{

public:
    Tensor()=default;
    Tensor(int dim, int size):dim_(dim), size_(size){};
    Tensor(const Tensor& other) = default;
    Tensor& operator=(const Tensor& other) = default;

    int dim() const { return dim_; }
    int size() const { return size_; }

private:
    int dim_;
    int size_;
    // Add other tensor properties and methods as needed
};