#include <iostream>
#include <string>
#include <vector>

// Function to check divisibility by a prime using bitwise operations
bool isDivisibleBy(int num, int prime) {
    int multiplier = 1; // Initially, the multiplier for the last digit
    int result = 0;

    while (num > 0) {
        int lastDigit = num & 1; // Get the last binary digit (equivalent to % 2)
        result = (result + lastDigit * multiplier) % prime;
        multiplier = (multiplier * 2) % prime; // Update multiplier for next bit
        num = num >> 1; // Right shift to remove the last bit
    }

    return result == 0;
}

int main() {
    std::vector<int> primes = {3, 37, 89}; // Example set of primes for testing
    int number;

    std::cout << "Enter a number to check divisibility: ";
    std::cin >> number;

    for (int prime : primes) {
        if (isDivisibleBy(number, prime)) {
            std::cout << "The number " << number << " is divisible by " << prime << ".\n";
        } else {
            std::cout << "The number " << number << " is NOT divisible by " << prime << ".\n";
        }
    }

    return 0;
}
