#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{

  int num = 0;
  int count = 0;
  int prev = 0;
  int max_count = 0;

  try {
    while (std::cin >> num && num != 0) {
      if (count > 0 && num == prev) {
        count++;
      }

      else {
        count = 1;
      }

      if (count > max_count){
        max_count = count;
      }

      prev = num;
    }
    if (std::cin.fail()) {
      throw std::invalid_argument("not a number entered");
    }
  }

  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << "\n";
    return 1;
  }

  std::cout << max_count << "\n";
  return 0;
}
