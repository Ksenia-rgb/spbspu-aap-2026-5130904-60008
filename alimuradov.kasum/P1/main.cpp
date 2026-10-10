#include <iostream>
#include <cstdlib>

int main() {
    int prev = 0;
    int cur = 0;
    int curLen = 0;
    int maxLen = 0;

    if (!(std::cin >> prev)) {
        std::cout << "Not a sequence\n";
        return EXIT_FAILURE;
    }

    while (std::cin >> cur) {
        curLen = (cur < prev) ? (curLen ? curLen + 1 : 2) : 0;
        if (curLen > maxLen) maxLen = curLen;
        prev = cur;
    }

    if (!std::cin.eof()) {
        std::cout << "Not a number\n";
        return EXIT_FAILURE;
    }

    std::cout << maxLen << "\n";
    return EXIT_SUCCESS;
}
