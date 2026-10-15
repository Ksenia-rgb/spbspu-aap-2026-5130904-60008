#include <iostream>
int main()
{
  int current_number = 0;
  int prevision_number = 0;
  int cnt = 0;
  bool is_first = true;
  if (!(std::cin >> current_number))
  {
    std::cerr << "Invalid input.\n";
    return 1;
  }
  while (current_number != 0)
  {
    if (!is_first)
    {
      if (current_number > prevision_number)
      {
        cnt++;
      }
    }
    else
    {
      is_first = false;
    }
    prevision_number = current_number;
    if (!(std::cin >> current_number))
    {
      std::cerr << "Invalid input.\n";
      return 1;
    }
  }
  std::cout << cnt << "\n";
  return 0;
}
