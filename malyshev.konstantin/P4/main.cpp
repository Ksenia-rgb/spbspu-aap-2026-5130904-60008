#include <iostream>
#include <limits>
#include <new>
#include <cctype>
#include <cstring>

namespace malyshev
{
  const int ERROR_MEMORY = 1;
  const int ERROR_INPUT = 2;
  const size_t CAPACITY = 16;

  char* readLine(std::istream& input);
  char* convertCase(char* dst, const char* src) noexcept;
}

int main()
{
  char* source = nullptr;
  char* res = nullptr;

  try
  {
    source = malyshev::readLine(std::cin);

    if (std::cin.bad())
    {
      delete[] source;
      std::cerr << "ERROR INPUT\n";
      return malyshev::ERROR_INPUT;
    }

    if (source == nullptr)
    {
      std::cerr << "ERROR MEMORY\n";
      return malyshev::ERROR_MEMORY;
    }

    const size_t length = std::strlen(source);
    if (length == std::numeric_limits< size_t >::max())
    {
      delete[] source;
      std::cerr << "ERROR MEMORY\n";
      return malyshev::ERROR_MEMORY;
    }

    res = new (std::nothrow) char[length + 1];
    if (res == nullptr)
    {
      delete[] source;
      std::cerr << "ERROR MEMORY\n";
      return malyshev::ERROR_MEMORY;
    }

    malyshev::convertCase(res, source);
    std::cout << res << '\n';

    delete[] res;
    delete[] source;
    return 0;
  }
  catch (const std::exception&)
  {
    delete[] res;
    delete[] source;
    std::cerr << "ERROR MEMORY\n";
    return malyshev::ERROR_MEMORY;
  }
}

namespace malyshev
{
  char* readLine(std::istream& input)
  {
    size_t capacity = CAPACITY;
    size_t size = 0;

    char* data = new (std::nothrow) char[capacity];
    if (data == nullptr)
    {
      return nullptr;
    }

    char ch = '\0';
    if (!input.get(ch))
    {
      delete[] data;
      return nullptr;
    }

    if (ch != '\n')
    {
      data[size++] = ch;
      while (input.get(ch) && ch != '\n')
      {
        if (size == capacity - 1)
        {
          if (capacity > std::numeric_limits< std::size_t >::max() / 2)
          {
            delete[] data;
            return nullptr;
          }

          const size_t newCapacity = capacity * 2;
          char* const exp = new (std::nothrow) char[newCapacity];
          if (exp == nullptr)
          {
            delete[] data;
            return nullptr;
          }

          for (size_t i = 0; i < size; i++)
          {
            exp[i] = data[i];
          }

          delete[] data;
          data = exp;
          capacity = newCapacity;
        }

        data[size++] = ch;
      }
    }

    data[size] = '\0';
    return data;
  }

  char* convertCase(char* dst, const char* src) noexcept
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; i++)
    {
      const unsigned char ch = static_cast< unsigned char >(src[i]);
      dst[j++] = static_cast< char >(std::tolower(ch));
    }
    dst[j] = '\0';
    return dst;
  }
}
