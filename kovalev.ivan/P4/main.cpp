#include <iostream>
#include <cstring>
#include <cctype>
#include <new>
#include <limits>
#include <cstddef>

namespace kovalev
{
  const int ERROR_CODE = 1;
  const int INITIAL_CAPACITY = 8;
  const int MULTIPLICATION_NUMBER = 2;
  char * readLine(std::istream & input);
  char * removeNum(char * dst, const char * src) noexcept;
}

int main()
{
  char * const line = kovalev::readLine(std::cin);
  if (line == nullptr)
  {
    std::cerr << "Memory error\n";
    return kovalev::ERROR_CODE;
  }
  if (line[0] == '\0' && std::cin.fail())
  {
    delete[] line;
    std::cerr << "Input error\n";
    return kovalev::ERROR_CODE;
  }
  char * line_without_num = new (std::nothrow) char[std::strlen(line) + 1];
  if (line_without_num == nullptr)
  {
    delete[] line;
    std::cerr << "Memory error\n";
    return kovalev::ERROR_CODE;
  }
  line_without_num = kovalev::removeNum(line_without_num, line);
  std::cout << line_without_num << '\n';
  delete[] line;
  delete[] line_without_num;
  return 0;
}

namespace kovalev
{
  char * readLine(std::istream & input)
  {
    std::size_t capacity = INITIAL_CAPACITY;
    std::size_t size = 0;
    char * data = new (std::nothrow) char[capacity];
    if (data == nullptr)
    {
      return nullptr;
    }
    char ch = '\0';
    while (input.get(ch) && ch != '\n')
    {
      if (size == capacity - 1)
      {
        if (capacity > std::numeric_limits< std::size_t >::max() / MULTIPLICATION_NUMBER)
        {
          delete[] data;
          return nullptr;
        }
        const std::size_t newCapacity = capacity * MULTIPLICATION_NUMBER;
        char * const expanded_data = new (std::nothrow) char[newCapacity];
        if (expanded_data == nullptr)
        {
          delete[] data;
          return nullptr;
        }
        for (std::size_t i = 0; i < size; i++)
        {
          expanded_data[i] = data[i];
        }
        delete[] data;
        capacity = newCapacity;
        data = expanded_data;
      }
      data[size++] = ch;
    }
    data[size] = '\0';
    return data;
  }

  char * removeNum(char * dst, const char * src) noexcept
  {
    std::size_t j = 0;
    for (std::size_t i = 0; src[i] != '\0'; i++)
    {
      const unsigned char num = static_cast< unsigned char >(src[i]);
      if (!std::isdigit(num))
      {
        dst[j++] = src[i];
      }
    }
    dst[j] = '\0';
    return dst;
  }
}
