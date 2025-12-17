#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

void processFile(std::string file, std::vector<Range>& freshIds) {
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
    }
    inputFile.close();
}

std::vector<Range> mergeRanges(std::vector<Range>& freshIds) {
    std::vector<Range> mergedRanges;
    mergedRanges.push_back(freshIds[0]);
    // std::cout << "freshIds: " << std::endl;
    // for (Range& ids : freshIds) {
    //     std::cout << ids.start << "-" << ids.end << std::endl;
    // }

    for (int i = 1; i < freshIds.size(); i++) {
        Range& last = mergedRanges.back(); // need reference to the last element in vector
        Range curr = freshIds[i];
        // std::cout << "last: " << last.start << "-" << last.end << std::endl;
        // std::cout << "curr: " << curr.start << "-" << curr.end << std::endl;

        if (curr.start <= last.end) {
            last.end = std::max(last.end, curr.end);
        } else {
            mergedRanges.push_back(curr);
        }
    }

    std::cout << "mergedRanges: " << std::endl;
    for (Range& ids : mergedRanges) {
        std::cout << ids.start << "-" << ids.end << std::endl;
    }

    return mergedRanges;
}

size_t countFreshIngredients(std::vector<Range>& mergedRanges) {
    size_t total = 0;

    for (Range& r : mergedRanges) {
        total += r.end - r.start + 1;
    }

    return total;
}

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
    std::vector<Range> freshIds;

    processFile(argv[1], freshIds);

    std::sort(freshIds.begin(), freshIds.end(), [](const Range& lhs, const Range& rhs) {
        return lhs.start < rhs.start;
    });

    std::vector<Range> mergedRanges = mergeRanges(freshIds);

    size_t total = countFreshIngredients(mergedRanges);

    std::cout << "total: " << total << std::endl;

    return 0;
}