#include <iostream>

int main() {
    int x;

    if (!(std::cin >> x)) {
        std::cerr << "Error: input is not a valid integer sequence\n";
        return 1;
    }

    if (x == 0) {
        std::cerr << "Error: sequence is too short\n";
        return 2;
    }

    int mx = x;
    int cnt = 1;

    while (true) {
        if (!(std::cin >> x)) {
            std::cerr << "Error: input is not a valid integer sequence\n";
            return 1;
        }

        if (x == 0) {
            break;
        }

        if (x > mx) {
            mx = x;
            cnt = 1;
        } else if (x == mx) {
            cnt++;
        }
    }

    std::cout << cnt << '\n';
    return 0;
}
