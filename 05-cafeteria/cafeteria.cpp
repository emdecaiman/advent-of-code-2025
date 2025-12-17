#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Range {
    std::size_t start;
    std::size_t end;
};

void processFreshIds(std::vector<Range>& freshIds, std::string& line) {
    std::stringstream ss(line);
    std::string start_str, end_str;
    char delimiter = '-';
    
    if (std::getline(ss, start_str, delimiter) && std::getline(ss, end_str)) {
        Range range;
        range.start = stol(start_str);
        range.end = stol(end_str);
        freshIds.push_back(range);
    }
}

void processFile(std::string file, std::vector<Range>& freshIds, std::vector<size_t>& ids) {
    std::ifstream inputFile;
    inputFile.open(file);
    std::string line;

    if (inputFile.is_open()) {
        // parse the freshIds
        while (std::getline(inputFile, line)) {
            processFreshIds(freshIds, line);

            if (line == "") {
                break;
            }
        }

        while (std::getline(inputFile, line)) {
            ids.push_back(stol(line));
        }
        
    }
    inputFile.close();
}

int countAvailableIds(std::vector<Range>& freshIds, std::vector<size_t>& ids) {
    int total = 0;

    for (long id : ids) {
        for (Range& range : freshIds) {
            if (id >= range.start && id <= range.end) {
                total++;
                break;
            }
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
    std::vector<Range> freshIds;
    std::vector<size_t> ids;

    processFile(argv[1], freshIds, ids);
    int total = countAvailableIds(freshIds, ids);

    std::cout << "freshIds: ";
    for (Range& ids : freshIds) {
        std::cout << ids.start << "-" << ids.end << std::endl;
    }

    std::cout << std::endl << "ids: ";
    for (size_t i : ids) {
        std::cout << i << " ";
    }

    
    std::cout << "total: " << total << std::endl;

    return 0;
}