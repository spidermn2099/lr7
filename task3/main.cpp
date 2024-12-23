#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

// Helper function: Convert a character to its numeric value in the given base
int charToValue(char c) {
    if (isdigit(c)) {
        return c - '0'; // Numeric digits
    } else if (isalpha(c)) {
        return toupper(c) - 'A' + 10; // Letters (A-Z) for bases > 10
    }
    return -1; // Invalid character
}

// Helper function: Convert a numeric value to its character representation in the given base
char valueToChar(int value) {
    if (value < 10) {
        return '0' + value; // Numeric digits
    } else {
        return 'A' + (value - 10); // Letters (A-Z)
    }
}

// Function to add two numbers in a given base
std::string addNumbers(const std::string& num1, const std::string& num2, int base) {
    std::string result;
    int carry = 0;

    // Align the lengths by padding with zeros
    size_t maxLen = std::max(num1.size(), num2.size());
    std::string num1Padded = std::string(maxLen - num1.size(), '0') + num1;
    std::string num2Padded = std::string(maxLen - num2.size(), '0') + num2;

    // Perform addition from right to left
    for (int i = maxLen - 1; i >= 0; --i) {
        int digit1 = charToValue(num1Padded[i]);
        int digit2 = charToValue(num2Padded[i]);
        int sum = digit1 + digit2 + carry;

        carry = sum / base;
        result.push_back(valueToChar(sum % base));
    }

    // Handle final carry
    if (carry > 0) {
        result.push_back(valueToChar(carry));
    }

    // Reverse the result to get the final number
    std::reverse(result.begin(), result.end());
    return result;
}

// Function to subtract two numbers in a given base
std::string subtractNumbers(const std::string& num1, const std::string& num2, int base) {
    std::string result;
    int borrow = 0;

    // Align the lengths by padding with zeros
    size_t maxLen = std::max(num1.size(), num2.size());
    std::string num1Padded = std::string(maxLen - num1.size(), '0') + num1;
    std::string num2Padded = std::string(maxLen - num2.size(), '0') + num2;

    // Perform subtraction from right to left
    for (int i = maxLen - 1; i >= 0; --i) {
        int digit1 = charToValue(num1Padded[i]);
        int digit2 = charToValue(num2Padded[i]) + borrow;

        if (digit1 < digit2) {
            digit1 += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(valueToChar(digit1 - digit2));
    }

    // Remove leading zeros
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    // Reverse the result to get the final number
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    int base;
    std::string num1, num2;
    char operation;

    std::cout << "Enter the base of the number system (2-36): ";
    std::cin >> base;
    if (base < 2 || base > 36) {
        std::cerr << "Invalid base! Base must be between 2 and 36." << std::endl;
        return 1;
    }

    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;
    std::cout << "Enter the operation (+ or -): ";
    std::cin >> operation;

    std::string result;
    if (operation == '+') {
        result = addNumbers(num1, num2, base);
    } else if (operation == '-') {
        result = subtractNumbers(num1, num2, base);
    } else {
        std::cerr << "Invalid operation! Only + and - are supported." << std::endl;
        return 1;
    }

    std::cout << "The result is: " << result << std::endl;
    return 0;
}
