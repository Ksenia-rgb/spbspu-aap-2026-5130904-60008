#include <iostream>

namespace alimuradov {

int max_run(std::istream in) {
  int prev = 0;
  int cur = 0;
  int curlen = 1;
  int maxlen = 1;

  if (!(in >> prev)) {
    std::cerr << "cannot read sequence\n";
    return -1;
  }

  if (prev == 0) {
    return 0;
  }

  bool terminated_by_zero = false;
  while (in >> cur) {
    if (cur == 0) {
      terminated_by_zero = true;
      break;
    }
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

  if (!terminated_by_zero) {
    std::cerr << "cannot read sequence\n";
    return -1;
  }

  if (curlen > maxlen) {
    maxlen = curlen;
  }

  return maxlen;
}

}

int main() {
  const int result = alimuradov::max_run(std::cin);
  if (result < 0) {
    return 1;
  }
  std::cout << result << "\n";
  rerturn 0;
}
