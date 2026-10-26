#include <iostream>

namespace alimuradov {

int maxRun(std::istream& in) {
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

  bool terminatedByZero = false;
  while (in >> cur) {
    if (cur == 0) {
      terminatedByZero = true;
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

  if (!terminatedByZero) {
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
  int result = alimuradov::maxRun(std::cin);
  if (result < 0) {
    return 1;
  }
  std::cout << result << "\n";
  return 0;
}
