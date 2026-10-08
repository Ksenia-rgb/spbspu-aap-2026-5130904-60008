#include <iostream>

int main()
{
  int x = 0;
  if (!(std::cin >> x)) {
    std::cerr << "input is not a sequence of integers\n";
    return 1;
  }

  if (x == 0) {
    std::cerr << "sequence is empty\n";
    return 2;
  }
  int max_val = x;
  int count_after = 0;

  if (!(std::cin >> x)) {
    std::cerr << "sequence is empty\n";
    return 1;
  }

  while (x != 0) {
    if (x > max_val) {
      max_val = x;
      count_after = 0;
    } else {
      count_after++;
    }

    if (!(std::cin >> x)) {
      std::cerr << "sequence is empty\n";
      return 1;
    }
  }
  std::cout << count_after << "\n";
  return 0;
}
