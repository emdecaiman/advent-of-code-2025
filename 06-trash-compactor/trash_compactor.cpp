#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<std::string>>;
using Row = std::vector<std::string>;

void processRow(Grid& worksheet, std::string& line, Row& row) {
    std::stringstream ss(line);
    std::string token;

    while (ss >> token) {
        row.push_back(token);
    }
}

void processFile(std::string file, Grid& worksheet) {
    std::ifstream inputFile;
    std::string line;
    inputFile.open(file);

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            worksheet.push_back({});
            processRow(worksheet, line, worksheet.back());
        }
    }

    for (auto& row : worksheet) {
        for (auto& s : row) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }

    inputFile.close();
}

size_t doCalculation(const Grid& worksheet, std::string operation, size_t col, size_t rowSize) {
    size_t total = stoul(worksheet[0][col]);

    for (int row = 1; row < rowSize - 1; row++) {
        if (operation == "+") {
            total += stoul(worksheet[row][col]);
        } else {
            total *= stoul(worksheet[row][col]);
        }
    }

    std::cout << "total: " << total << std::endl;
    return total;
}

size_t calculateGrandTotal(const Grid& worksheet) {
    size_t rowSize = worksheet.size();
    size_t colSize = worksheet[0].size();
    size_t grandTotal = 0;

    for (int col = 0; col < colSize; col++) {
        std::string operation = worksheet[rowSize - 1][col];
        std::cout << "operation: " << operation << std::endl;
        grandTotal += doCalculation(worksheet, operation, col, rowSize);
    }

    return grandTotal;
}

int main(int argc, char* argv[]) {
    Grid worksheet;

    processFile(argv[1], worksheet);
    size_t grandTotal = calculateGrandTotal(worksheet);

    std::cout << "grandTotal: " << grandTotal << std::endl;

    return 0;
}