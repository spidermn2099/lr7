#include <iostream>
#include <vector>
#include <bitset>

void identifyPoisonedBarrel() {
    const int numBarrels = 241;
    const int numSlaves = 5;
    int poisonedBarrel;

    std::cout << "Enter the poisoned barrel number (0 to 240): ";
    std::cin >> poisonedBarrel;

    if (poisonedBarrel < 0 || poisonedBarrel >= numBarrels) {
        std::cerr << "Invalid barrel number!" << std::endl;
        return;
    }

    // Step 1: Represent barrel assignments in binary
    std::cout << "\nBarrel Assignments (Binary Representation):\n";
    for (int barrel = 0; barrel < numBarrels; ++barrel) {
        std::bitset<numSlaves> binary(barrel);
        std::cout << "Barrel " << barrel << ": " << binary << "\n";
    }

    // Step 2: Determine which slaves die based on the poisoned barrel
    std::bitset<numSlaves> poisonedPattern(poisonedBarrel);
    std::cout << "\nAfter the first test, the poisoned barrel is identified by these slaves dying:\n";
    for (int i = 0; i < numSlaves; ++i) {
        if (poisonedPattern[i]) {
            std::cout << "Slave " << i + 1 << " dies.\n";
        } else {
            std::cout << "Slave " << i + 1 << " survives.\n";
        }
    }

    // Output the poisoned barrel
    std::cout << "\nThe poisoned barrel is Barrel " << poisonedBarrel << ".\n";
}

int main() {
    identifyPoisonedBarrel();
    return 0;
}
