#ifndef ARRAYMANAGER_H
#define ARRAYMANAGER_H

#include <iostream>
#include <utility>

template<typename T>
class ArrayManager {
private:
    T* ptr;
    size_t size;

public:
    // 1. Default constructor
    ArrayManager() : ptr(nullptr), size(0) {
        std::cout << "Default constructor called - creating empty ArrayManager" << std::endl;
    }

    // 2. Constructor taking a raw pointer
    ArrayManager(T* arr, size_t sz) : ptr(arr), size(sz) {
        std::cout << "Pointer constructor called - taking ownership of array with size " << size << std::endl;
    }

    // 3. Move constructor
    ArrayManager(ArrayManager&& other) noexcept : ptr(other.ptr), size(other.size) {
        std::cout << "Move constructor called - moving array with size " << size << std::endl;
        other.ptr = nullptr;
        other.size = 0;
    }

    // 4. Move assignment operator
    ArrayManager& operator=(ArrayManager&& other) noexcept {
        std::cout << "Move assignment operator called" << std::endl;
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            size = other.size;
            other.ptr = nullptr;
            other.size = 0;
        }
        std::cout << "  Moved array with size " << size << ", original object resources released" << std::endl;
        return *this;
    }

    // Delete copy constructor and copy assignment (exclusive ownership)
    ArrayManager(const ArrayManager&) = delete;
    ArrayManager& operator=(const ArrayManager&) = delete;

    // Destructor
    ~ArrayManager() {
        if (ptr != nullptr) {
            std::cout << "Destructor called - releasing array with size " << size << std::endl;
            delete[] ptr;
        }
        else {
            std::cout << "Destructor called - empty ArrayManager, nothing to release" << std::endl;
        }
    }

    // 5. get() - Returns the raw pointer
    T* get() const {
        return ptr;
    }

    // Get array size
    size_t getSize() const {
        return size;
    }

    // 6. swap() - Swap two ArrayManager objects
    void swap(ArrayManager& other) noexcept {
        std::cout << "swap() called" << std::endl;
        std::swap(ptr, other.ptr);
        std::swap(size, other.size);
    }

    // Subscript operator overload for array element access
    T& operator[](size_t index) {
        return ptr[index];
    }

    const T& operator[](size_t index) const {
        return ptr[index];
    }

    // Check if empty
    bool isNull() const {
        return ptr == nullptr;
    }

    // Release ownership
    T* release() {
        std::cout << "release() called - releasing array ownership" << std::endl;
        T* temp = ptr;
        ptr = nullptr;
        size = 0;
        return temp;
    }
};

#endif // ARRAYMANAGER_H