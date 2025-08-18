#include <iostream>
#include <string>
#include "../includes/my_vector.hpp"



int main() {
    std::cout << "=== Copy Constructor ===\n";
    MyVector<int> v1;
    for (int i = 0; i < 5; i++) v1.push_back(i);
    
    MyVector<int> v2 = v1; // Copy
    std::cout << "v2 after copy: ";
    for (auto& x : v2) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Copy Assignment (copy-and-swap) ===\n";
    MyVector<int> v3;
    v3 = v1; // Copy assignment
    std::cout << "v3 after copy assign: ";
    for (auto& x : v3) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Move Constructor ===\n";
    MyVector<int> v4 = std::move(v1); // Move
    std::cout << "v4 after move: ";
    for (auto& x : v4) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "v1 size after move: " << v1.getSize() << "\n";

    std::cout << "\n=== Move Assignment ===\n";
    MyVector<int> v5;
    v5 = std::move(v2); // Move assignment
    std::cout << "v5 after move assign: ";
    for (auto& x : v5) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "v2 size after move: " << v2.getSize() << "\n";

    std::cout << "\n=== Resize & Reserve ===\n";
    MyVector<int> v6(3, 42);
    std::cout << "v6: ";
    for (auto& x : v6) std::cout << x << " ";
    std::cout << " size=" << v6.getSize() << " capacity=" << v6.getCapacity() << "\n";
    
    v6.resize(6, 99);
    std::cout << "v6 after resize(6, 99): ";
    for (auto& x : v6) std::cout << x << " ";
    std::cout << " size=" << v6.getSize() << " capacity=" << v6.getCapacity() << "\n";

    v6.reserve(20);
    std::cout << "v6 after reserve(20): size=" << v6.getSize() << " capacity=" << v6.getCapacity() << "\n";

    return 0;
}
