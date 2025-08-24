#pragma once // my_vector.hpp

#include <iostream>
#include <memory>


template <typename T>
class MyVector
{
private:
    T *data_;
    size_t capacity_;
    size_t size_;

public:
    MyVector();
    MyVector(std::size_t n, const T &value);
    ~MyVector();

    MyVector(const MyVector &other);                // copy constructor
    MyVector &operator=(const MyVector &other);     // copy assignment operator
    MyVector(MyVector &&other) noexcept;            // move constructor
    MyVector &operator=(MyVector &&other) noexcept; // move assignment operator

    void push_back(const T &value);
    void push_back(T &&value);// For rvalue references
    void pop_back();
    void erase(std::size_t index); // Remove element at index
    T &operator[](std::size_t index);
    const T &operator[](std::size_t index) const;
    const T &at(std::size_t index) const;
    T &at(std::size_t index);

    std::size_t getSize() const;
    std::size_t getCapacity() const;
    bool isEmpty() const;

    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    void clear(); // Clear the vector by resetting size to 0
    void reserve(std::size_t newCapacity);
    void resize(std::size_t newSize, const T &value = T());
    void insert(std::size_t index, const T &value);
    void swap(MyVector &other);

    void shrink_to_fit();

    class Iterator
    {
    private:
        T *ptr;

    public:
        Iterator(T *p) : ptr(p) {}
        T &operator*() { return *ptr; }
        Iterator &operator++()
        {
            ++ptr;
            return *this;
        }
        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
    };

    class ConstIterator
    {
    private:
        const T *ptr;

    public:
        ConstIterator(const T *p) : ptr(p) {}
        const T &operator*() const { return *ptr; }
        ConstIterator &operator++()
        {
            ++ptr;
            return *this;
        }
        bool operator!=(const ConstIterator &other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }
    ConstIterator begin() const { return ConstIterator(data_); }
    ConstIterator end() const { return ConstIterator(data_ + size_); }
};

// Implementation

template <typename T>
MyVector<T>::MyVector() : data_(nullptr), capacity_(0), size_(0) {}

template <typename T>
MyVector<T>::MyVector(std::size_t n, const T &value) : data_(nullptr), capacity_(n), size_(n)
{
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}

template <typename T>
MyVector<T>::~MyVector()
{
    delete[] data_;
}

template <typename T>
MyVector<T>::MyVector(const MyVector &other) : data_(nullptr), capacity_(other.capacity_), size_(other.size_)
{
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_)
{
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &other)
{
    if (this != &other)
    {
        MyVector temp(other);
        swap(temp);
    }
    return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector &&other) noexcept
{
    if (this != &other)
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    return *this;
}

template <typename T>
void MyVector<T>::push_back(const T &value)
{
    if (size_ >= capacity_)
    {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

template <typename T>
void MyVector<T>::push_back(T &&value) // For rvalue references
{
    if (size_ >= capacity_)
    {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template <typename T>
void MyVector<T>::pop_back()
{
    if (size_ > 0)
    {
        data_[size_ - 1].~T();
        --size_;
    }
}

template <typename T>
void MyVector<T>::erase(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size_ - 1; ++i)
    {
        data_[i] = std::move(data_[i + 1]);
    }
    data_[size_ - 1].~T();
    --size_;
}

template <typename T>
T &MyVector<T>::operator[](std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
const T &MyVector<T>::operator[](std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
T &MyVector<T>::at(std::size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
const T &MyVector<T>::at(std::size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
std::size_t MyVector<T>::getSize() const
{
    return size_;
}

template <typename T>
std::size_t MyVector<T>::getCapacity() const
{
    return capacity_;
}

template <typename T>
bool MyVector<T>::isEmpty() const
{
    return size_ == 0;
}

template <typename T>
T &MyVector<T>::front()
{
    if (isEmpty())
    {
        throw std::out_of_range("Vector is empty");
    }
    return data_[0];
}

template <typename T>
const T &MyVector<T>::front() const
{
    if (isEmpty())
    {
        throw std::out_of_range("Vector is empty");
    }
    return data_[0];
}

template <typename T>
T &MyVector<T>::back()
{
    if (isEmpty())
    {
        throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T>
const T &MyVector<T>::back() const
{
    if (isEmpty())
    {
        throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T>
void MyVector<T>::clear()
{
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i].~T();
    }
    size_ = 0;
}

template <typename T>
void MyVector<T>::reserve(std::size_t newCapacity)
{
    if (newCapacity <= capacity_)
        return;
    T *newData = new T[newCapacity];
    for (size_t i = 0; i < size_; ++i)
    {
        newData[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}

template <typename T>
void MyVector<T>::resize(std::size_t newSize, const T &value)
{
    if (newSize < size_)
    {
        for (std::size_t i = newSize; i < size_; ++i)
        {
            data_[i].~T();
        }
        size_ = newSize;
    }
    else if (newSize > size_)
    {
        if (newSize > capacity_)
        {
            reserve(newSize);
        }
        for (std::size_t i = size_; i < newSize; ++i)
        {
            data_[i] = value;
        }
        size_ = newSize;
    }
}

template <typename T>
void MyVector<T>::insert(std::size_t index, const T &value)
{
    if (index > size_)
    {
        throw std::out_of_range("Index out of range");
    }
    if (size_ >= capacity_)
    {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    for (size_t i = size_; i > index; --i)
    {
        data_[i] = std::move(data_[i - 1]);
    }
    data_[index] = value;
    ++size_;
}

template <typename T>
void MyVector<T>::swap(MyVector &other)
{
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
void MyVector<T>::shrink_to_fit()
{
    if (size_ < capacity_)
    {
        T *newData = new T[size_];
        for (size_t i = 0; i < size_; ++i)
        {
            newData[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = newData;
        capacity_ = size_;
    }
}