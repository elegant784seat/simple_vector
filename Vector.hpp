#ifndef VECTOR_VECTOR_HPP
#define VECTOR_VECTOR_HPP
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Mashallah {
    T* data_;
    size_t size_;
    size_t capacity_;
    void scale_capacity() {
        if (size_ < capacity_) {
            return;
        }
        size_t new_capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
        T* new_data = nullptr;
        try {
            new_data = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
        } catch (...) {
            delete[] new_data;
            throw;
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Mashallah() {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
    Mashallah(const Mashallah& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    Mashallah& operator=(const Mashallah& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    Mashallah(Mashallah&& other) noexcept {
        data_ = other.data_;
        other.data_ = nullptr;
        size_ = other.size_;
        other.size_ = 0;
        capacity_ = other.capacity_;
        other.capacity_ = 0;
    }
    Mashallah& operator=(Mashallah&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = other.data_;
        other.data_ = nullptr;
        size_ = other.size_;
        other.size_ = 0;
        capacity_ = other.capacity_;
        other.capacity_ = 0;

        return *this;
    }
    ~Mashallah() {
        delete[] data_;
        data_ = nullptr;
    }
    void push_back(const T& val) {
        scale_capacity();
        data_[size_++] = val;
    }
    void push_back(T&& val) {
        scale_capacity();
        data_[size_++] == std::move(val);
    }
    size_t get_size() const {
        return size_;
    }
    size_t get_capacity() const {
        return capacity_;
    }
    const T& operator[](size_t i) const {
        return data_[i];
    }
    T& operator[](size_t i) {
        return data_[i];
    }
    const T& at(size_t i) const {
        if (i >= size_) {
            throw std::out_of_range("Mashallah::at");
        }
        return data_[i];
    }
    T& at(size_t i) {
        if (i >= size_) {
           throw std::out_of_range("Mashallah::at");
        }
        return data_[i];
    }
    void clear() {
        size_ = 0;
    }
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Mashallah::pop_back");
        }
        --size_;
    }
    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        T* new_data = nullptr;
        try {
            new_data = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
        } catch (...) {
            delete[] new_data;
            throw;
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    void resize(size_t new_size) {
        if (new_size < size_) {
            size_ = new_size;
        } else if (new_size > size_) {
            reserve(new_size);
            for (size_t i = size_; i < new_size; ++i) {
                data_[i] = T();
            }
            size_ = new_size;
        }
    }
    bool empty() const {
        return size_ == 0;
    }
    T& front() {
        if (size_ == 0) {
            throw std::out_of_range("Mashallah::front");
        }
        return data_[0];
    }
    const T& front() const {
        if (size_ == 0) {
            throw std::out_of_range("Mashallah::front");
        }
        return data_[0];
    }
    T& back() {
        if (size_ == 0) {
            throw std::out_of_range("Mashallah::back");
        }
        return data_[size_ - 1];
    }
    const T& back() const {
        if (size_ == 0) {
            throw std::out_of_range("Mashallah::back");
        }
        return data_[size_ - 1];
    }
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Mashallah::erase");
        }
        for (size_t i = index; i < size_; ++i) {
            data_[i - 1] = std::move(data_[i]);
        }
        --size_;
    }
    void swap(Mashallah& other) noexcept {
        using std::swap;
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
        swap(data_, other.data_);
    }
    void shrink_to_fit() {
        if (capacity_ == size_) {
            return;
        }
        if (size_ == 0) {
            delete[] data_;
            data_ = nullptr;
            capacity_ = 0;
            return;
        }
        T* new_data = new T[size_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;

    }
    T* data() noexcept {
        return data_;
    }
    const T* data() const noexcept {
        return data_;
    }
    explicit Mashallah(size_t count, const T& val = T()) {
        data_ = new T[count];
        size_ = count;
        capacity_ = count;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = val;
        }
    }
};
#endif //VECTOR_VECTOR_HPP
