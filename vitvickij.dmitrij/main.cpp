#include <iostream>
#include <stdexcept>
#include <limits>

int main()
{
    int num = 0;
    int count = 0;
    int max1 = std::numeric_limits<int>::min();
    int max2 = std::numeric_limits<int>::min();

    try {
        while (std::cin >> num && num != 0) {
            count++;
            if (num > max1) {
                max2 = max1;
                max1 = num;
            } else if (num > max2) {
                max2 = num;
            }
        }

        if (std::cin.fail()) {
            throw std::invalid_argument("not a number entered");
        }

        if (count < 2) {
            throw std::runtime_error("sequence is too short");
        }

        std::cout << max2 << "\n";

    } catch (const std::invalid_argument &ex) {
        std::cerr << ex.what() << "\n";
        return 1;
    } catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << "\n";
        return 2;
    }

    return 0;
}
