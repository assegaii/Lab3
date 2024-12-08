#ifndef SEQUENTIAL_CONTAINER_H
#define SEQUENTIAL_CONTAINER_H

#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
class SequentialContainer {
private:
    T* data;
    size_t capacity;
    size_t current_size;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    SequentialContainer(size_t initial_capacity = 10) 
        : capacity(initial_capacity), current_size(0) {
        data = new T[capacity];
    }

    ~SequentialContainer() {
        delete[] data;
    }

    SequentialContainer(const SequentialContainer&) = delete;
    SequentialContainer& operator=(const SequentialContainer&) = delete;

    SequentialContainer(SequentialContainer&& other) noexcept
        : data(other.data), capacity(other.capacity), current_size(other.current_size) {
        other.data = nullptr;
        other.capacity = 0;
        other.current_size = 0;
    }

    SequentialContainer& operator=(SequentialContainer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            current_size = other.current_size;
            other.data = nullptr;
            other.capacity = 0;
            other.current_size = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (current_size == capacity) {
            reallocate(capacity * 1.5);
        }
        data[current_size++] = value;
    }

    void push_front(const T& value) {
        if (current_size == capacity) {
            reallocate(capacity * 1.5);
        }
        for (size_t i = current_size; i > 0; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[0] = value;
        ++current_size;
    }

    void insert(size_t index, const T& value) {
        if (index > current_size) {
            throw std::out_of_range("Index out of range");
        }
        if (current_size == capacity) {
            reallocate(capacity * 1.5);
        }
        for (size_t i = current_size; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = value;
        ++current_size;
    }

    void erase(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --current_size;
    }

    size_t size() const {
        return current_size;
    }

    T& operator[](size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* ptr) : ptr(ptr) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    
    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(data + current_size); }
};

#endif 
