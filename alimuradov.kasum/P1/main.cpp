#include <iostream>

namespace alimuradov {

int maxRun(std::istream &in) {
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
      curlen = 1;
    }

    if (curlen > maxlen) {
      maxlen = curlen;
    }

    prev = cur;
  }

  if (!terminated_by_zero) {
    std::cerr << "cannot read sequence\n";
    return -1;
  }

  return maxlen;
}

}


int main() {
  int result = alimuradov::maxRun(std::cin);
  if (result < 0) {
    return 1;
  }
  std::cout << result << "\n";
  return 0;
}
