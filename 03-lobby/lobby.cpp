#include <iostream>
#include <string>

int largestJoltageInCurrentBank(std::string& batteryBank) {
    std::string joltage = "";
    
    // find the first largest battery in bank, cannot be the last one since we need two batteries
    char largestFirstBattery = '0';
    int idxLargestFirstBattery;
    for (int i = 0; i < batteryBank.size() - 1; i++) {
        if (batteryBank[i] > largestFirstBattery) {
            largestFirstBattery = batteryBank[i];
            idxLargestFirstBattery = i;
        }
    }
    joltage.push_back(largestFirstBattery);

    // find the second largest battery starting after the idx of first
    char largestSecondBattery = '0';
    for (int i = idxLargestFirstBattery + 1; i < batteryBank.size(); i++) {
        if (batteryBank[i] > largestSecondBattery) {
            largestSecondBattery = batteryBank[i];
        }
    }
    joltage.push_back(largestSecondBattery);

    std::cout << "joltage: " << joltage << std::endl;

    return std::stoi(joltage);
}

int main() {
    std::string batteryBank;
    int totalJoltage = 0;

    while (std::cin >> batteryBank) {
        std::cout << "processing bank: " << batteryBank << std::endl;
        totalJoltage += largestJoltageInCurrentBank(batteryBank);
    }

    std::cout << totalJoltage << std::endl;
    return 0;
}
