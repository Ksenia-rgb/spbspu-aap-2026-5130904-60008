#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <new>
namespace koshutin
{
  constexpr std::size_t CAP = 16;

  char *replaceSymbol(char *dst, const char *src, char a, char b) noexcept;
  char *readLine(std::istream &input);
}

int main()
{
  char *result = nullptr;
  char *source = nullptr;

  try
  {
    source = koshutin::readLine(std::cin);
    if (source == nullptr)
    {
      std::cerr << "Cannot allocate input buffer" << "\n";
      return 1;
    }
    if (source[0] == '\0')
    {
      delete[] source;
      std::cerr << "Empty input" << "\n";
      return 1;
    }
    const std::size_t length = std::strlen(source);
    if (length == std::numeric_limits< std::size_t >::max())
    {
      delete[] source;
      std::cerr << "Output buffer size overflow" << "\n";
      return 1;
    }
    result = new (std::nothrow) char[length + 1];
    if (result == nullptr)
    {
      delete[] source;
      std::cerr << "Cannot allocate output buffer" << "\n";
      return 1;
    }
    koshutin::replaceSymbol(result, source, 'c', 'b');
    std::cout << result << "\n";
  }
  catch (const std::bad_alloc &)
  {
    delete[] source;
    delete[] result;
    std::cerr << "Not enough memory" << "\n";
    return 1;
  }
  catch (const std::exception &e)
  {
    delete[] source;
    delete[] result;
    std::cerr << "Error:" << e.what() << "\n";
    return 2;
  }
  delete[] result;
  delete[] source;
  return 0;
}

namespace koshutin
{
  char *replaceSymbol(char *dst, const char *src, char a, char b) noexcept
  {
    size_t j = 0;
    const unsigned char aa = static_cast< unsigned char >(a);
    for (size_t i = 0; src[i] != '\0'; i++)
    {
      const unsigned char ch = static_cast< unsigned char >(src[i]);
      if (ch == aa)
      {
        dst[j++] = b;
      }
      else
      {
        dst[j++] = src[i];
      }
    }
    dst[j] = '\0';
    return dst;
  }

  char *readLine(std::istream &input)
  {
    size_t capacity = CAP;
    size_t size = 0;
    char *data = new (std::nothrow) char[capacity];
    if (data == nullptr)
    {
      return nullptr;
    }
    try
    {
      char ch = '\0';
      while (input.get(ch) && ch != '\n')
      {
        if (size + 1 >= capacity)
        {
          if (capacity > std::numeric_limits< std::size_t >::max() / 2)
          {
            delete[] data;
            return nullptr;
          }
          const std::size_t newCapacity = capacity * 2;
          char *const expanded = new (std::nothrow) char[newCapacity];
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
