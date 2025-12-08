#include <iostream>
#include <string>
#include <stack>

const int BATTERIES_LENGTH = 12;

std::string convertStackToString(std::stack<char>& stack) {
    std::string joltage = "";

    while (!stack.empty()) {
        joltage += stack.top();
        stack.pop();
    }

    std::reverse(joltage.begin(), joltage.end());
    return joltage;
}

long largestJoltageInCurrentBank(std::string& batteryBank) {
    std::string joltage = "";
    
    std::stack<char> stack;
    int toRemove = batteryBank.size() - BATTERIES_LENGTH;

    for (int i = 0; i < batteryBank.size(); i++) {
        
        while (!stack.empty() && toRemove > 0 && stack.top() < batteryBank[i]) {
            toRemove -= 1;
            stack.pop();
        }
        stack.push(batteryBank[i]);
    }

    while (toRemove > 0) {
        toRemove -=1;
        stack.pop();
    }

    joltage = convertStackToString(stack);
    // using a stack

    std::cout << "joltage: " << joltage << std::endl;

    return std::stol(joltage);
}

int main() {
    std::string batteryBank;
    long totalJoltage = 0;

    while (std::cin >> batteryBank) {
        std::cout << "processing bank: " << batteryBank << std::endl;
        totalJoltage += largestJoltageInCurrentBank(batteryBank);
    }

    std::cout << totalJoltage << std::endl;
    return 0;
}
