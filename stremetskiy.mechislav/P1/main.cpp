#include <iostream>
#include <climits>
#include <stdexcept>

int main()
{
  int num = -3;
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
        throw std::logic_error("Sequence is too short");
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
    return 1;
  }
  catch (const std::logic_error &ex)
  {
    std::cerr << "Invalid input: " << ex.what() << "\n";
    return 2;
  }
  catch (const std::range_error &ex)
  {
    std::cerr << "Value out of range: " << ex.what() << "\n";
    return 2;
  }
  catch (...)
  {
    std::cerr << "Another error\n";
    return 2;
  }

  std::cout << "Number of max values in the sequence: " << count_max << "\n";
  return 0;
}
