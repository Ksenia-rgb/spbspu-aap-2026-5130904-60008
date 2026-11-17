#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>

namespace teplikov
{
  constexpr int SUCCESS_CODE = 0;
  constexpr int FAIL_CODE = 1;

  constexpr std::size_t MAX_SIZE = std::numeric_limits< std::size_t >::max();
  constexpr std::size_t INITIAL_CAPACITY = 8;
  constexpr std::size_t GROWTH_FACTOR = 2;

  char *readLine(std::istream &);
  int hasRepeats(const char *) noexcept;
}

int main()
{
  char *input = nullptr;

  try
  {
    input = teplikov::readLine(std::cin);

    if (input == nullptr)
    {
      if (std::cin.bad())
      {
        std::cerr << "Input error\n";
      }
      else
      {
        std::cerr << "Empty input\n";
      }
      return teplikov::FAIL_CODE;
    }

    std::cout << teplikov::hasRepeats(input) << '\n';

    delete[] input;
    return teplikov::SUCCESS_CODE;
  }
  catch (const std::bad_alloc &)
  {
    delete[] input;
    std::cerr << "Not enough memory\n";
    return teplikov::FAIL_CODE;
  }
}

char *teplikov::readLine(std::istream &input)
{
  char *data = new char[INITIAL_CAPACITY];
  std::size_t capacity = INITIAL_CAPACITY;
  std::size_t size = 0;
  char ch = '\0';

  try
  {
    while (input.get(ch) && (ch != '\n'))
    {
      if (size == (capacity - 1))
      {
        if (capacity > (MAX_SIZE / GROWTH_FACTOR))
        {
          throw std::bad_alloc();
        }

        const std::size_t newCapacity = capacity * GROWTH_FACTOR;
        char *const newData = new char[newCapacity];

        for (std::size_t i = 0; i < size; ++i)
        {
          newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
      }

      data[size++] = ch;
    }

    if (input.bad() || ((size == 0) && input.eof()))
    {
      delete[] data;
      return nullptr;
    }

    data[size] = '\0';
    return data;
  }
  catch (...)
  {
    delete[] data;
    throw;
  }
}

int teplikov::hasRepeats(const char *str) noexcept
{
  for (std::size_t i = 0; str[i] != '\0'; ++i)
  {
    if (std::strchr(str + i + 1, str[i]) != nullptr)
    {
      return 1;
    }
  }

  return 0;
}
