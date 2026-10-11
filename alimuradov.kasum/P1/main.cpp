#include <iostream>

int main()
{
  int prev = 0;
  int cur = 0;
  int curlen = 1;
  int maxlen = 1;
  if (!(std::cin >> prev)) {
    std::cout << 0 << "\n";
    return 0;
  }

  if (prev == 0) {
    std::cout << 0 << "\n";
    return 0;
  }

  while (std::cin >> cur && cur != 0) {
    if (cur <= prev) {
      curlen++;
    } else {
      if (curlen > maxlen) {
        maxlen = curlen;
      }
      curlen = 1;
    }
    prev = cur;
  }

  if (curlen > maxlen) {
    maxlen = curlen;
  }

  std::cout << maxlen << "\n";
  return 0;
}
