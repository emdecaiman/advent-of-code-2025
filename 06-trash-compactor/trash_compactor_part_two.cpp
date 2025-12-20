#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<char>>;
using Row = std::vector<char>;

void processRow(Grid& worksheet, std::string& line, Row& row) {
    for (int i = 0; i < line.size(); i++) {
        row.push_back(line[i]);
    }
}

void processOperations(Row& operations, std::string& line) {
    std::stringstream ss(line);
    char token;

    while (ss >> token) {
        operations.push_back(token);
    }
}

void processFile(std::string file, Grid& digits, Row& operations) {
    std::ifstream inputFile;
    std::string line;
    inputFile.open(file);

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (line[0] != '*' and line[0] != '+') {
                digits.push_back({});
                processRow(digits, line, digits.back());
            } else {
                processOperations(operations, line);
            }
        }
    }

    for (auto& row : digits) {
        for (auto& s : row) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }

    for (auto& o : operations) {
        std::cout << o << " ";
    }
    std::cout << std::endl
              << std::endl;

    inputFile.close();
}

size_t computeSum(std::vector<std::string>& numbers) {
    size_t sum = 0;
    for (auto& n : numbers) {
        std::cout << n << std::endl;
        sum += std::stol(n);
    }

    std::cout << "sum: " << sum << std::endl;
    return sum;
}

size_t computeProduct(std::vector<std::string>& numbers) {
    size_t product = 1;
    for (auto& n : numbers) {
        std::cout << n << std::endl;
        product *= std::stol(n);
    }

    std::cout << "product: " << product << std::endl;
    return product;
}

size_t calculateGrandTotal(const Grid& digits, const Row& operations) {
    size_t rowSize = digits.size();
    size_t colSize = digits[0].size() - 1;
    size_t grandTotal = 0;
    int currOperation = operations.size() - 1;
    std::vector<std::string> numbers;

    for (int col = colSize; col > -1; col--) {
        std::string currDigit;

        for (int row = 0; row < rowSize; row++) {
            if (digits[row][col] != ' ') {
                currDigit.push_back(digits[row][col]);
            }
        }

        if (!currDigit.empty()) {
            numbers.push_back(currDigit);
        }

        if (currDigit.empty() || col == 0) {
            if (operations[currOperation] == '+') {
                grandTotal += computeSum(numbers);
            } else {
                grandTotal += computeProduct(numbers);
            }
            numbers.clear();
            currOperation--;
        }
    }

    return grandTotal;
}

int main(int argc, char* argv[]) {
    Grid digits;
    Row operations;

    processFile(argv[1], digits, operations);
    size_t grandTotal = calculateGrandTotal(digits, operations);

    std::cout << "grandTotal: " << grandTotal << std::endl;

    return 0;
}