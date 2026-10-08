#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
  int current = 0, previous = 0, cur_len = 0, max_len = 0;

  try {
    while (std::cin >> current) {
      if (current == 0) {
        break;
      }

      if (current <= previous) {
        ++cur_len;
      }

      else {
        cur_len = 1;
      }

      if (cur_len > max_len) {
        max_len = cur_len;
      }

      previous = current;
    }
    if (!std::cin) {
      throw std::invalid_argument("Not a sequence");
    }

  }

  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << "\n";
    std::exit(1);
  }

  std::cout << max_len << "\n";

  return 0;
}
