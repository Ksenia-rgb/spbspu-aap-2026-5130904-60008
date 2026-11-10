#include <cstddef>
#include <cstdio>
#include <iostream>
#include <new>
#include <limits>

namespace babikov
{
  const int EXIT_FAIL_CODE = 1;
  const int EXIT_SUCCESS_CODE = 0;
  const int DUPLICATE_FOUND = 1;
  const int DUPLICATE_NOT_FOUND = 0;
  const std::size_t INITIAL_CAPACITY = 2;

  int increaseLine(char*&, std::size_t&, std::size_t&);
  int readLine(char*&, std::size_t&, std::size_t&);
  int findAdjacentEqual(const char*);
}

int main()
{
  std::size_t size = 0;
  std::size_t capacity = babikov::INITIAL_CAPACITY;

  char* str = new (std::nothrow) char[capacity];

  if (str == nullptr)
  {
    std::cerr << "Memory allocation error\n";
    return babikov::EXIT_FAIL_CODE;
  }

  if (babikov::readLine(str, size, capacity) != babikov::EXIT_SUCCESS_CODE)
  {
    delete[] str;
    std::cerr << "Input or memory allocation error\n";
    return babikov::EXIT_FAIL_CODE;
  }

  const int result = babikov::findAdjacentEqual(str);

  std::cout << result << '\n';

  delete[] str;

  return babikov::EXIT_SUCCESS_CODE;
}

int babikov::increaseLine(char*& str, std::size_t& size, std::size_t& capacity)
{
  if (capacity > std::numeric_limits< std::size_t >::max() / 2)
  {
    return babikov::EXIT_FAIL_CODE;
  }

  const std::size_t new_capacity = capacity * 2;

  char* const temp = new (std::nothrow) char[new_capacity];

  if (temp == nullptr)
  {
    return babikov::EXIT_FAIL_CODE;
  }

  for (std::size_t i = 0; i < size; ++i)
  {
    temp[i] = str[i];
  }

  delete[] str;

  str = temp;
  capacity = new_capacity;

  return babikov::EXIT_SUCCESS_CODE;
}

int babikov::readLine(char*& str, std::size_t& size, std::size_t& capacity)
{
  int symbol = std::getchar();

  if (symbol == EOF)
  {
    return babikov::EXIT_FAIL_CODE;
  }

  while (symbol != '\n' && symbol != EOF)
  {
    if (size >= capacity - 1)
    {
      if (babikov::increaseLine(str, size, capacity) == babikov::EXIT_FAIL_CODE)
      {
        return babikov::EXIT_FAIL_CODE;
      }
    }

    str[size] = static_cast< char >(symbol);
    ++size;

    symbol = std::getchar();
  }

  str[size] = '\0';

  return babikov::EXIT_SUCCESS_CODE;
}

int babikov::findAdjacentEqual(const char* str)
{
  for (std::size_t i = 0; str[i] != '\0' && str[i + 1] != '\0'; ++i)
  {
    if (str[i] == str[i + 1])
    {
      return babikov::DUPLICATE_FOUND;
    }
  }

  return babikov::DUPLICATE_NOT_FOUND;
}
