#include <iostream>
#include <stdexcept>
#include <cstdlib>

constexpr int bad_input = 1;
constexpr int range_error = 2;

int main()
{
  const int min_value = 2;
  int max1 = 0;
  int max2 = 0;
  int num = 0;
  int size = 0;
  try
  {
    while (std::cin >> num && num != 0)
    {
      size++;
      if (size == 1)
      {
        max1 = num;
      }
      else if (num > max1)
      {
        max2 = max1;
        max1 = num;
      }
      else if (num > max2 || size == min_value)
      {
        max2 = num;
      }
    }
    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::invalid_argument("Invalid_argument");
    }
    if (size < min_value)
    {
      throw std::out_of_range("Not_enough_values");
    }
  }
  catch (const std::invalid_argument &ex)
  {
    std::cerr << ex.what() << "\n";
    std::exit(bad_input);
  }
  catch (const std::out_of_range &ex)
  {
    std::cerr << ex.what() << "\n";
    std::exit(range_error);
  }
  std::cout << max2 << "\n";
  return 0;
}
