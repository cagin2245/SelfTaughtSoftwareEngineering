#include <iostream>
#include <cstring>
using namespace std;



bool isNumeric(const char * str) {
    if (str == nullptr || strlen(str) == 0) {
        return false;
    }
    for (size_t i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+') {
            return false;
        }
    }
    return true;
}

char* processString(const char* input) {
    if (input == nullptr) {
        cerr << "Error: Null input provided." << endl;
        return nullptr;
    }

    size_t len = strlen(input);
    if (isNumeric(input)) {
        cerr << "Error: Input string cannot be numeric." << endl;
        return nullptr;
    }
    if (len == 0) {
        cerr << "Error: Empty input string provided." << endl;
        return nullptr;
    }

    char* output = new char[len + 1];
    strcpy(output, input);
    return output;
}
    
const char* TEST_STRING = "test";

int main()
{
    cout << "Hello, World!" << endl;
    cout << "Please enter a string: ";
    string input;
    getline(cin, input);
    printf("You entered: %s\n", processString(input.c_str()));
    // Example usage of the constant
    // printf("Constant test string: %s\n", TEST_STRING);
    return 0;
}