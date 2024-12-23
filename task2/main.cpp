#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to convert binary number in direct code to additional code (2's complement)
std::vector<int> toAdditionalCode(const std::string& binary) {
    std::vector<int> result(binary.size());
    bool isNegative = (binary[0] == '-');

    // Copy binary digits to the result array
    for (size_t i = (isNegative ? 1 : 0); i < binary.size(); ++i) { // O(n)
        result[i - (isNegative ? 1 : 0)] = binary[i] - '0';
    }

    // If negative, calculate 2's complement
    if (isNegative) {
        for (size_t i = 0; i < result.size(); ++i) { // O(n)
            result[i] = 1 - result[i];
        }

        // Add 1 to complete the 2's complement conversion
        int carry = 1;
        for (int i = result.size() - 1; i >= 0 && carry; --i) { // O(n)
            int sum = result[i] + carry;
            result[i] = sum % 2;
            carry = sum / 2;
        }
    }

    return result;
}

// Function to perform binary addition in additional code
std::vector<int> addBinaryNumbers(const std::vector<int>& a, const std::vector<int>& b) {
    size_t maxSize = std::max(a.size(), b.size());
    std::vector<int> result(maxSize + 1, 0); // +1 for potential overflow

    // Add from the least significant bit to the most significant bit
    int carry = 0;
    for (int i = 0; i < maxSize; ++i) { // O(n)
        int bitA = (a.size() > i) ? a[a.size() - 1 - i] : 0; // Access bits from the end
        int bitB = (b.size() > i) ? b[b.size() - 1 - i] : 0;

        int sum = bitA + bitB + carry;
        result[result.size() - 1 - i] = sum % 2;
        carry = sum / 2;
    }

    // Handle final carry
    result[0] = carry;

    return result;
}

// Function to convert binary in additional code back to direct code
std::vector<int> toDirectCode(const std::vector<int>& additionalCode) {
    if (additionalCode[0] == 0) {
        return additionalCode; // Already positive
    }

    // Negative case: Perform 2's complement conversion back
    std::vector<int> result(additionalCode);

    // Subtract 1
    int borrow = 1;
    for (int i = result.size() - 1; i >= 0 && borrow; --i) { // O(n)
        if (result[i] == 0) {
            result[i] = 1;
            borrow = 0;
        } else {
            result[i] = 0;
        }
    }

    // Invert bits
    for (size_t i = 0; i < result.size(); ++i) { // O(n)
        result[i] = 1 - result[i];
    }

    return result;
}

// Function to print the result in direct code
void printBinary(const std::vector<int>& binary) {
    if (binary[0] == 1) {
        std::cout << "-";
    }
    bool leadingZero = true;
    for (size_t i = (binary[0] == 1 ? 1 : 0); i < binary.size(); ++i) { // O(n)
        if (binary[i] == 1) leadingZero = false;
        if (!leadingZero) std::cout << binary[i];
    }
    if (leadingZero) std::cout << "0";
    std::cout << std::endl;
}

int main() {
    std::string binary1, binary2;

    std::cout << "Enter the first binary number: ";
    std::cin >> binary1;
    std::cout << "Enter the second binary number: ";
    std::cin >> binary2;

    // Convert to additional code
    std::vector<int> additionalCode1 = toAdditionalCode(binary1);
    std::vector<int> additionalCode2 = toAdditionalCode(binary2);

    // Perform addition
    std::vector<int> sumInAdditionalCode = addBinaryNumbers(additionalCode1, additionalCode2);

    // Convert the result back to direct code
    std::vector<int> resultInDirectCode = toDirectCode(sumInAdditionalCode);

    // Print the result
    std::cout << "The sum in direct code is: ";
    printBinary(resultInDirectCode);

    return 0;
}
