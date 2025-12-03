#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    int curr = 50;
    int password = 0;
    std::string word;
    while (std::cin >> word) {
        char direction = word[0];
        int num = std::stoi(word.substr(1));
        if (direction == 'R') {
            curr = (curr + num) % 100;
        } else {
            curr = (curr - num) % 100;
            if (curr < 0) {
                curr += 100;
            }
        }

        if (curr == 0) {
            password += 1;
        }
    }
    std::cout << password << std::endl;
    return 0;
}