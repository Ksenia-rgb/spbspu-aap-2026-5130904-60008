#include <iostream>

int main()
{
  int cn = 0;
  int prev = 0;
  int now = 0;
  int next = 0;

  if (!(std::cin >> prev))
  {
    std::cerr << "invalid input\n";
    return 1;
  }

  if (prev == 0)
  {
    const int empty_subsequence_code = 2;
    std::cerr << "too small subsequence\n";
    return empty_subsequence_code;
  }

  if (!(std::cin >> now))
  {
    std::cerr << "invalid input\n";
    return 1;
  }

  if (now == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  while (std::cin >> next)
  {
    if (next == 0)
    {
      break;
    }
    if (now < prev && now < next)
    {
      cn++;
    }
    prev = now;
    now = next;
  }

  if (!std::cin)
  {
    std::cerr << "invalid input\n";
    return 1;
  }

  std::cout << cn << "\n";
  return 0;
}
