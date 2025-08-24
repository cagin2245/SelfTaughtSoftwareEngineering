#include <iostream>
#include "my_vector.hpp"

void test_basic_push()
{
    MyVector<int> v;
    std::cout << "Initial capacity: " << v.getCapacity() << "\n";

    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i * 10);
        std::cout << "push_back(" << i * 10 << ") size=" << v.getSize()
                  << " capacity=" << v.getCapacity() << "\n";
    }

    std::cout << "Elements: ";
    for (auto &x : v) std::cout << x << " ";
    std::cout << "\n\n";
}

void test_insert_erase()
{
    MyVector<int> v;
    for (int i = 1; i <= 5; ++i) v.push_back(i); // 1 2 3 4 5

    v.insert(2, 99); // 1 2 99 3 4 5
    std::cout << "After insert: ";
    for (auto &x : v) std::cout << x << " ";
    std::cout << "\n";

    v.erase(3); // remove element at index 3 → 1 2 99 4 5
    std::cout << "After erase: ";
    for (auto &x : v) std::cout << x << " ";
    std::cout << "\n\n";
}

void test_resize_reserve()
{
    MyVector<int> v(5, 7); // [7,7,7,7,7]
    std::cout << "Init: ";
    for (auto &x : v) std::cout << x << " ";
    std::cout << "\n";

    v.resize(3); // shrink
    std::cout << "After resize(3): size=" << v.getSize() << "\n";

    v.resize(6, 42); // grow with value
    std::cout << "After resize(6,42): ";
    for (auto &x : v) std::cout << x << " ";
    std::cout << "\n";

    v.reserve(20);
    std::cout << "After reserve(20): capacity=" << v.getCapacity() << "\n\n";
}

void test_copy_move()
{
    MyVector<int> v1;
    for (int i = 0; i < 5; ++i) v1.push_back(i);

    MyVector<int> v2 = v1; // copy ctor
    std::cout << "Copied v2: ";
    for (auto &x : v2) std::cout << x << " ";
    std::cout << "\n";

    MyVector<int> v3 = std::move(v1); // move ctor
    std::cout << "Moved v3: ";
    for (auto &x : v3) std::cout << x << " ";
    std::cout << "\n";

    MyVector<int> v4;
    v4 = v2; // copy assignment
    std::cout << "Copy assigned v4: ";
    for (auto &x : v4) std::cout << x << " ";
    std::cout << "\n";

    MyVector<int> v5;
    v5 = std::move(v2); // move assignment
    std::cout << "Move assigned v5: ";
    for (auto &x : v5) std::cout << x << " ";
    std::cout << "\n\n";
}

void test_accessors()
{
    MyVector<std::string> v;
    v.push_back("hello");
    v.push_back("world");

    std::cout << "front: " << v.front() << "\n";
    std::cout << "back: " << v.back() << "\n";
    std::cout << "at(1): " << v.at(1) << "\n";

    try {
        std::cout << v.at(5) << "\n";
    } catch (const std::out_of_range &e) {
        std::cout << "Caught exception on at(5): " << e.what() << "\n";
    }
    std::cout << "\n";
}

void test_shrink_to_fit()
{
    MyVector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);

    std::cout << "Before shrink: capacity=" << v.getCapacity()
              << " size=" << v.getSize() << "\n";

    for (int i = 0; i < 5; ++i) v.pop_back();

    std::cout << "After pops: capacity=" << v.getCapacity()
              << " size=" << v.getSize() << "\n";

    v.shrink_to_fit();
    std::cout << "After shrink_to_fit: capacity=" << v.getCapacity()
              << " size=" << v.getSize() << "\n\n";
}

int main()
{
    test_basic_push();
    test_insert_erase();
    test_resize_reserve();
    test_copy_move();
    test_accessors();
    test_shrink_to_fit();
}
