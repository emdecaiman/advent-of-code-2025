#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    int curr = 50;
    int password = 0;
    std::string word;
    while (std::cin >> word) {
        char direction = word[0];
        int num = std::stoi(word.substr(1));
        int hits = 0;

        if (direction == 'R') {
            hits = (curr + num) / 100;
            curr = (curr + num) % 100;
        } else {
            if (curr == 0) {
                hits = num / 100;
            } else if (num < curr) {
                hits = 0;
            } else {
                hits = 1 + (num - curr) / 100;
            }

            curr = (curr - num) % 100;
            if (curr < 0) {
                curr += 100;
            }

        }
        password += hits;
    }


    std::cout << password << std::endl;
    return 0;
}