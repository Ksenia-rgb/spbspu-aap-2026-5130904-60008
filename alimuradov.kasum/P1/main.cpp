#include <iostream>
#include <cstdlib>

int main()
{
  int prev = 0;
  int cur = 0;
  int curlen = 1;
  int maxlen = 1;

  if (!(std::cin >> prev)) {
    std::cout << 0 << "\n";
    return EXIT_SUCCESS;
  }

  while (std::cin >> cur && cur != 0) {
    if (cur <= prev) {
      curlen++;
      } else {
        if (curlen > maxlen) maxlen = curlen;
        curlen = 1;
      }
      prev = cur;
  }

  if (std::cin.fail() && !std::cin.eof()) {
    std::cout << "Not a number\n"
    return EXIT_FAILURE;
  }

  if (curlen > maxlen) maxlen = curlen;

  std::cout << maxlen << "\n"
  return EXIT_SUCCESS;
}
