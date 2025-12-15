#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> NEIGHBORS = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

std::vector<char> processRow(std::string& row) {
    std::vector<char> temp;

    for (int i = 0; i < row.size(); i++) {
        temp.push_back(row[i]);
    }

    return temp;
}

std::vector<std::vector<char>> processGrid() {
    std::string row;
    std::vector<std::vector<char>> grid;
    while (std::cin >> row) {
        grid.push_back(processRow(row));
    }

    return grid;
}

bool validAccess(std::vector<std::vector<char>>& grid, int i, int j, int rowSize, int colSize) {
    if (grid[i][j] != '@') {
        return false;
    }

    // std::cout << "process i: " << i << " j: " << j << std::endl;

    int numRolls = 0;

    for (auto& n : NEIGHBORS) {
        int new_i = i + n.first;
        int new_j = j + n.second;

        bool withinRowBounds = new_i >= 0 && new_i < rowSize;
        bool withinColBounds = new_j >= 0 && new_j < colSize;

        if (withinRowBounds && withinColBounds && grid[new_i][new_j] == '@') {
            // std::cout << "neigbor new_i: " << new_i << " new_j: " << new_j << std::endl;
            numRolls += 1;
        }
    }

    return numRolls < 4;
}

void updateGrid(std::vector<std::vector<char>>& grid, int i, int j) {
    grid[i][j] = 'x';
}

void printGrid(std::vector<std::vector<char>>& grid, int rowSize, int colSize) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void findValidRolls(std::vector<std::vector<char>>& grid, int rowSize, int colSize, std::vector<std::pair<int, int>>& toBeRemoved, int& total) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (validAccess(grid, i, j, rowSize, colSize)) {
                total += 1;
                toBeRemoved.push_back({i, j});
            }
        }
    }
}

int countRolls(std::vector<std::vector<char>>& grid, int rowSize, int colSize) {
    int total = 0;

    std::vector<std::pair<int, int>> toBeRemoved;

    findValidRolls(grid, rowSize, colSize, toBeRemoved, total);

    while (!toBeRemoved.empty()) {
        for (auto& n : toBeRemoved) {
            updateGrid(grid, n.first, n.second);
        }

        std::cout << std::endl;
        printGrid(grid, rowSize, colSize);

        toBeRemoved.clear();

        findValidRolls(grid, rowSize, colSize, toBeRemoved, total);
    }

    return total;
}

int main() {
    std::vector<std::vector<char>> grid = processGrid();
    int rowSize = grid.size();
    int colSize = grid[0].size();

    printGrid(grid, rowSize, colSize);

    std::cout << countRolls(grid, rowSize, colSize) << std::endl;

    return 0;
}