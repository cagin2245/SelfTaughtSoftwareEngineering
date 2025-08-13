#include <iostream>
#include <cstring>

char * processString(const char *input) {
    if (input == nullptr) {
        std::cerr << "Error: Null input provided." << std::endl;
        return nullptr;
    }

    size_t len = strlen(input);
    if (len == 0) {
        std::cerr << "Error: Empty input string provided." << std::endl;
        return nullptr;
    }

    char *output = new char[len + 1];
    strcpy(output, input);
    return output;
}
char * processString(const char *input, size_t &length) {
    if (input == nullptr) {
        std::cerr << "Error: Null input provided." << std::endl;
        return nullptr;
    }

    length = strlen(input);
    if (length == 0) {
        std::cerr << "Error: Empty input string provided." << std::endl;
        return nullptr;
    }
    printf("Processing string of length: %zu\n", length);
    char *output = new char[length + 1];
    strcpy(output, input);
    return output;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Please enter a string: ";
    std::string input;
    std::getline(std::cin, input);
    size_t length;
    length = input.length();
    char *processed = processString(input.c_str(), length);
    
    if (processed) {
        std::cout << "You entered: " << processed << std::endl;
        std::cout << "Length of processed string: " << length << std::endl;
        delete[] processed; // Free allocated memory
    } else {
        std::cerr << "Failed to process the input string." << std::endl;
    }   

    return 0;
}