#include <cstddef>
#include <cstdio>
#include <iostream>
#include <new>

namespace dumina
{
  const int success_code = 0;
  const int failure_code = 1;

  const char replace_from = 'c';
  const char replace_to = 'b';
  const char new_line = '\n';
  const char null_terminator = '\0';

  const std::size_t initial_capacity = 16;
  const std::size_t growth_factor = 2;

  const char * const read_error = "UNABLE TO ALLOCATE MEMORY FOR INPUT STRING";
  const char * const result_error = "UNABLE TO ALLOCATE MEMORY FOR RESULT STRING";

  char * readLine();
  std::size_t length(const char * str);
  char * replaceSymbol(const char * src, char * dst, char from, char to);
}

int main()
{
  char * const input = dumina::readLine();
  if (input == nullptr)
  {
    std::cerr << dumina::read_error << '\n';
    return dumina::failure_code;
  }

  char * const result = new (std::nothrow) char[dumina::length(input) + 1];
  if (result == nullptr)
  {
    delete[] input;
    std::cerr << dumina::result_error << '\n';
    return dumina::failure_code;
  }

  dumina::replaceSymbol(input, result, dumina::replace_from, dumina::replace_to);
  std::cout << result << '\n';

  delete[] result;
  delete[] input;
  return dumina::success_code;
}

char * dumina::readLine()
{
  std::size_t capacity = initial_capacity;
  std::size_t size = 0;
  char * buffer = new (std::nothrow) char[capacity];
  if (buffer == nullptr)
  {
    return nullptr;
  }

  int symbol = std::getchar();
  if (symbol == EOF)
  {
    delete[] buffer;
    return nullptr;
  }
  while (symbol != EOF && symbol != new_line)
  {
    if (size + 1 >= capacity)
    {
      const std::size_t new_capacity = capacity * growth_factor;
      char * const new_buffer = new (std::nothrow) char[new_capacity];
      if (new_buffer == nullptr)
      {
        delete[] buffer;
        return nullptr;
      }
      for (std::size_t i = 0; i < size; ++i)
      {
        new_buffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = new_buffer;
      capacity = new_capacity;
    }
    buffer[size++] = static_cast< char >(symbol);
    symbol = std::getchar();
  }
  buffer[size] = null_terminator;
  return buffer;
}

std::size_t dumina::length(const char * str)
{
  std::size_t size = 0;
  while (str[size] != null_terminator)
  {
    ++size;
  }
  return size;
}

char * dumina::replaceSymbol(const char * src, char * dst, char from, char to)
{
  std::size_t i = 0;
  while (src[i] != null_terminator)
  {
    dst[i] = (src[i] == from) ? to : src[i];
    ++i;
  }
  dst[i] = null_terminator;
  return dst;
}
