#include <iostream>
#include "../../includes/calculator.hpp"

using namespace std;

int add(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    if (b == 0) {
        std::cerr << "Error: Division by zero." << std::endl;
        return 0; // or throw an exception
    }
    return a / b;
}
int modulus(int a, int b) {
    if (b == 0) {
        std::cerr << "Error: Division by zero." << std::endl;
        return 0; // or throw an exception
    }
    return a % b;
}
int power(int base, int exponent) {
    if (exponent < 0) {
        std::cerr << "Error: Negative exponent not supported." << std::endl;
        return 0; // or throw an exception
    }
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}
int square(int a) {
    return a * a;
}
int squareRoot(int a) {
    if (a < 0) {
        std::cerr << "Error: Negative input for square root." << std::endl;
        return 0; // or throw an exception
    }
    return static_cast<int>(sqrt(a));
}

