#include <iostream>
#include "../../includes/calculator.hpp"


using namespace std;



int main() {


    cout << "Calculator Operations:" << endl;
    int a, b;
    cout << "Enter two integers: ";
    
    cin >> a >> b;

    cout << "Addition: " << add(a, b) << endl;
    cout << "Subtraction: " << subtract(a, b) << endl;
    cout << "Multiplication: " << multiply(a, b) << endl;
    cout << "Division: " << divide(a, b) << endl;
    cout << "Power: " << power(a, b) << endl;
    cout << "Square of first number: " << square(a) << endl;
    cout << "Square root of first number: " << squareRoot(a) << endl;

    return 0;
}