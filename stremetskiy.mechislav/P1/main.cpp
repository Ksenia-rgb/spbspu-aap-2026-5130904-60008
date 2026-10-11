#include <iostream>
#include <climits>
#include <stdexcept>
#include <cstdlib>

constexpr int invalid_input_error = 1;
constexpr int range_error = 2;

int main()
{
  int num = INT_MIN;
  int count_max = 0;
  int max = INT_MIN;
  int size = 0;

  std::cout << "\nEnter a sequence of numbers separated by spaces: \n";

  try
  {
    while (num != 0)
    {
      if (!(std::cin >> num))
      {
        throw std::invalid_argument("expected int");
      }

      if (num == 0 && size == 0)
      {
        throw std::range_error("Sequence is too short");
      }

      if (num > max)
      {
        max = num;
        count_max = 1;
      }
      else if (num == max)
      {
        if (size < INT_MAX)
        {
          ++count_max;
        }
        else
        {
          throw std::range_error("Sequence is too big");
        }
      }
      ++size;
    }
  }

  catch (const std::invalid_argument &ex)
  {
    std::cerr << "Invalid input: " << ex.what() << "\n";
    std::exit(invalid_input_error);
  }
  catch (const std::range_error &ex)
  {
    std::cerr << "Value out of range: " << ex.what() << "\n";
    std::exit(range_error);
  }

  std::cout << "Number of max values in the sequence: " << count_max << "\n";
  return 0;
}
