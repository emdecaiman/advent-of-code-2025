#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> get_id_range(std::string id_range) {
    std::vector<std::string> id_pair;
    std::string temp;
    std::stringstream ss(id_range);
    char delimeter = '-';

    while (std::getline(ss, temp, delimeter)) {
        id_pair.push_back(temp);
    }
    return id_pair;
}

bool is_invalid(std::string id) {
    // find factors of id length
    std::vector<int> factors;
    for (int i = 1; i <= id.size(); i++) {
        if (i != id.size()) {
            if (id.size() % i == 0) {
                factors.push_back(i);
            }
        }
    }

    // process each factor to determine if the id is invalid
    for (int i = 0; i < factors.size(); i++) {
        int l = 0;
        int r = factors[i];
        bool all_match = true;

        while (r < id.size()) {
            // std::cout << "id[l]: " << id[l] << " id[r]: " << id[r] << std::endl;
            if (id[l] != id[r]) {
                all_match = false;
                break;
            }
            l++;
            r++;
        }
        // std::cout << all_match << std::endl;
        if (all_match) {
            std::cout << "invalid_id: " << id << std::endl;
            return true;
        }
    }

    return false;
}

long invalid_ids_sum(std::vector<std::string>& id_range) {
    long sum = 0;
    for (long id = std::stol(id_range[0]); id <= std::stol(id_range[1]); id++) {
        // std::cout << id << std::endl;
        // find the invalid ids
        if (is_invalid(std::to_string(id))) {
            sum += id;
        }
    }
    return sum;
}

int main() {
    std::string input;
    std::cin >> input;

    // process the input to get the product ID range separated by ','
    std::stringstream ss(input);

    char delimeter = ',';
    std::string temp;

    long invalid_id_sum = 0;
    while (std::getline(ss, temp, delimeter)) {
        // std::cout << temp << std::endl;
        std::vector<std::string> id_range = get_id_range(temp);

        std::cout << "firstId: " << id_range[0] << " secId: " << id_range[1] << std::endl;
        // find the invalid id
        invalid_id_sum += invalid_ids_sum(id_range);
    }

    std::cout << "invalid_id_sum: " << invalid_id_sum << std::endl;

    return 0;
}