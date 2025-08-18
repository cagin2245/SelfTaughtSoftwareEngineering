#pragma once // my_vector.hpp

#include <iostream>

using namespace std;

template <typename T>
class MyVector
{
private:
    T *data;
    size_t capacity;
    size_t size;

public:
    MyVector();
    MyVector(size_t n, const T &value);
    ~MyVector();

    MyVector(const MyVector &other);                // copy constructor
    MyVector &operator=(const MyVector &other);     // copy assignment operator
    MyVector(MyVector &&other) noexcept;            // move constructor
    MyVector &operator=(MyVector &&other) noexcept; // move assignment operator

    void push_back(const T &value);
    void pop_back();
    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    size_t getSize() const;
    size_t getCapacity() const;
    bool isEmpty() const;

    void reserve(size_t newCapacity);
    void resize(size_t newSize, const T &value = T());
    void swap(MyVector &other)
    {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(size, other.size);
    }
    // Iterators
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
    
    T *begin() { return data; }
    T *end() { return data + size; }
    const T *begin() const { return data; }
    const T *end() const { return data + size; }
};

template <typename T>
void MyVector<T>::reserve(size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        T *newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i)
        {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

template <typename T>
void MyVector<T>::resize(size_t newSize, const T &value)
{
    if (newSize < size)
    {
        // Küçültme → sadece size değişiyor
        size = newSize;
    }
    else if (newSize > size)
    {
        if (newSize > capacity)
        {
            reserve(newSize);
        }
        for (size_t i = size; i < newSize; ++i)
        {
            data[i] = value;
        }
        size = newSize;
    }
}

template <typename T>
size_t MyVector<T>::getSize() const
{
    return size;
}
template <typename T>
size_t MyVector<T>::getCapacity() const
{
    return capacity;
}
template <typename T>
bool MyVector<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
MyVector<T>::MyVector() : data(nullptr), capacity(0), size(0) {} // Default constructor initializes an empty vector
template <typename T>
MyVector<T>::MyVector(size_t n, const T &value) : capacity(n), size(n)
{
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = value; // Initialize with the given value
    }
}
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] data; // Destructor to free allocated memory
}
template <typename T>
MyVector<T>::MyVector(const MyVector &other) : capacity(other.capacity), size(other.size)
{
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i]; // Copy elements from the other vector
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other) noexcept : data(other.data), capacity(other.capacity), size(other.size)
{
    other.data = nullptr; // Leave the moved-from object in a valid state
    other.capacity = 0;
    other.size = 0;
}
template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &other)
{
    if (this != &other)
    {
        MyVector temp(other); // copy constructor çağrılır
        swap(temp);           // elimizdeki ile temp değişir
    }
    return *this;
}
template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector &&other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        capacity = other.capacity;
        size = other.size;
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}
template <typename T>
void MyVector<T>::push_back(const T &value)
{
    if (size >= capacity)
    {
        reserve(capacity == 0 ? 1 : capacity * 2); // Double the capacity if needed
    }
    data[size++] = value; // Add the new element and increment size
}
template <typename T>
void MyVector<T>::pop_back()
{
    if (size > 0)
    {
        data[size - 1].~T(); // Call destructor for the last element (primitive types don't need this but it's safe)
        --size;              // Decrement size to remove the last element
    }
}
template <typename T>
T &MyVector<T>::operator[](size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index]; // Return the element at the specified index
}
