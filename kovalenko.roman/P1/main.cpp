#include <iostream>

int main()
{
  int x;
  if (!(std::cin >> x)) {
    std::cerr << "input is not a sequence of integers\n";
    return 1;
  }

  if (x == 0) {
    std::cerr << "sequence is empty\n";
    return 2;
  }
  int maxVal = x;
  int countAfter = 0;

  if (!(std::cin >> x)) {
    std::cerr << "sequence is empty\n";
    return 1;
  }

  while (x != 0) {
    if (x > maxVal) {
      maxVal = x;
      countAfter = 0;
    } else {
      countAfter++;
    }

    if (!(std::cin >> x)) {
      std::cerr << "sequence is empty\n";
      return 1;
    }
  }
  std::cout << countAfter << "\n";
  return 0;
}
