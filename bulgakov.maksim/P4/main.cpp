#include <iostream>
#include <cctype>
#include <cstring>
#include <cstddef>
#include <new>

namespace bulgakov
{
  std::size_t bracketDigits(char* dst, const char* src) noexcept
  {
    std::size_t q = 0;
    for (std::size_t i = 0; src[i] != '\0'; ++i)
    {
      const unsigned char letter = static_cast< unsigned char >(src[i]);
      if (std::isalpha(letter))
      {
        dst[q++] = src[i];
      }
    }
    dst[q] = '\0';

    bool seen[256] = {};
    std::size_t non_rep_count = 0;

    for (std::size_t j = 0; j < q; ++j)
    {
      const unsigned char ch = static_cast< unsigned char >(dst[j]);
      if (!seen[ch])
      {
        seen[ch] = true;
        ++non_rep_count;
      }
    }

    return non_rep_count;
  }

  char* readline(std::istream& input) noexcept
  {
    const std::size_t initialCapacity = 16;
    std::size_t capacity = initialCapacity;
    std::size_t size = 0;
    char* data = new (std::nothrow) char[capacity];
    if (data == nullptr)
    {
      return nullptr;
    }

    char ch = '\0';
    while (input.get(ch) && ch != '\n')
    {
      if (size == capacity - 1)
      {
        const std::size_t newCapacity = capacity * 2;
        char* const expanded = new (std::nothrow) char[newCapacity];
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
}

int main()
{
  char* source = bulgakov::readline(std::cin);
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
  char* result = new (std::nothrow) char[length + 1];
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
