#include <iostream>
#include <cctype>
#include <cstring>
#include <cstddef>
#include <limits>
#include <new>

namespace bulgakov
{
  int bracketDigits(char* dst, const char* src) noexcept
  {
    std::size_t q = 0;
    for (std::size_t i = 0; src[i] != '\0'; ++i)
    {
      const unsigned char letter = static_cast<unsigned char>(src[i]);

      if (std::isalpha(letter))
      {
        dst[q++] = src[i];
      }
    }
    dst[q] = '\0';

    std::size_t dst_len = 0;
    while (dst[dst_len] != '\0')
    {
      dst_len++;
    }

    q = 0;
    char* resurce = new (std::nothrow) char[dst_len + 1]();
    if (resurce == nullptr)
    {
      return 0;
    }

    std::size_t non_rep_count = 0;

    for (std::size_t j = 0; j < dst_len && q < dst_len; ++j)
    {
      std::size_t currents = 0;

      for (std::size_t k = 0; k < q; ++k)
      {
        if (dst[j] == resurce[k])
        {
          currents++;
          break;
        }
      }

      if (currents == 0)
      {
        resurce[q++] = dst[j];
        non_rep_count++;
      }
    }

    resurce[q] = '\0';
    delete[] resurce;

    return non_rep_count;
  }

  char* readline(std::istream& input)
  {
    std::size_t capacity = 16;
    std::size_t size = 0;

    char* data = new (std::nothrow) char[capacity];
    if (data == nullptr)
    {
      return nullptr;
    }

    try
    {
      char ch = '\0';
      while (input.get(ch) && ch != '\n')
      {
        if (size == capacity - 1)
        {
          const std::size_t newCapacity = capacity * 2;
          char* expanded = new (std::nothrow) char[newCapacity];
          if (expanded == nullptr)
          {
            delete[] data;
            return nullptr;
          }

          for (std::size_t i = 0; i < size; ++i)
          {
            expanded[i] = data[i];
          }

          delete[] data;
          data = expanded;
          capacity = newCapacity;
        }
        data[size++] = ch;
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
}

int main()
{
  char* source = nullptr;
  char* result = nullptr;

  try
  {
    source = bulgakov::readline(std::cin);
    if (source == nullptr)
    {
      std::cerr << "Cannot allocate input buffer!\n";
      return 1;
    }
    if (std::cin.bad())
    {
      delete[] source;
      std::cerr << "Input error!\n";
      return 2;
    }

    const std::size_t length = std::strlen(source);

    result = new (std::nothrow) char[length + 1];
    if (result == nullptr)
    {
      delete[] source;
      std::cerr << "Cannot allocate output buffer!\n";
      return 1;
    }

    std::cout << bulgakov::bracketDigits(result, source) << '\n';

    delete[] result;
    delete[] source;
    return 0;
  }
  catch (const std::bad_alloc&)
  {
    delete[] result;
    delete[] source;
    std::cerr << "Not enough memory!\n";
    return 1;
  }
}

