#include <cstdlib>
#include <iostream>
#include <stdexcept>

constexpr int triple_size = 3;
constexpr int invalid_data_exit_code = 1;
constexpr int short_sequence_exit_code = 2;

bool isTriple(long long a = 0, long long b = 0, long long c = 0);

int main()
{
  long long num = 0;
  long long a = 0;
  long long b = 0;
  long long c = 0;
  int count = 0;
  int size = 0;

  try
  {
    while (std::cin >> num && num != 0)
    {
      ++size;

      a = b;
      b = c;
      c = num;

      if (size >= triple_size && isTriple(a, b, c))
      {
        ++count;
      }
    }

    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::invalid_argument("Invalid data format.");
    }

    if (size < triple_size)
    {
      throw std::range_error("Sequence is too short.");
    }

    std::cout << count << "\n";
    return 0;
  }
  catch (const std::invalid_argument &ex)
  {
    std::cerr << "Invalid_argument: " << ex.what() << "\n";
    std::exit(invalid_data_exit_code);
  }
  catch (const std::range_error &ex)
  {
    std::cerr << "Range_error: " << ex.what() << "\n";
    std::exit(short_sequence_exit_code);
  }
}

bool isTriple(long long a, long long b, long long c)
{
  if (a <= 0 || b <= 0 || c <= 0)
  {
    return false;
  }

  return (a * a + b * b == c * c) || (b * b + c * c == a * a) || (a * a + c * c == b * b);
}

