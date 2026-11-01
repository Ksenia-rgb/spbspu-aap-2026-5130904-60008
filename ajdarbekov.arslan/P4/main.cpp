#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace ajdarbekov
{
const int EXIT_CODE_SUCCESS = 0;
const int EXIT_CODE_FAIL = 1;
const size_t READLINE_ERROR = static_cast< size_t >(-1);
const char *const str2 = "abc_ef";

char *getuniquechars(char *buffer, const char *str1, const char *str2);
size_t readLine(size_t &size, size_t &capacity, char *&str1);
} // namespace ajdarbekov

int main()
{
  const size_t INITIAL_CAPACITY = 16;
  size_t capacity = INITIAL_CAPACITY;
  size_t size = 0;

  char *str1 = static_cast< char * >(std::malloc(capacity));
  if (!str1)
  {
    std::cerr << "Error: str1 malloc failed\n";
    return ajdarbekov::EXIT_CODE_FAIL;
  }

  size = ajdarbekov::readLine(size, capacity, str1);
  if (size == ajdarbekov::READLINE_ERROR || size == 0)
  {
    std::free(str1);
    std::cerr << "Error: Invalid or empty input\n";
    return ajdarbekov::EXIT_CODE_FAIL;
  }

  const size_t result_capacity = size + std::strlen(ajdarbekov::str2) + 1;

  char *buffer = static_cast< char * >(std::malloc(result_capacity));
  if (!buffer)
  {
    std::free(str1);
    std::cerr << "Error: buffer malloc failed\n";
    return ajdarbekov::EXIT_CODE_FAIL;
  }

  buffer = ajdarbekov::getuniquechars(buffer, str1, ajdarbekov::str2);

  std::cout << buffer << "\n";

  std::free(str1);
  std::free(buffer);
  return ajdarbekov::EXIT_CODE_SUCCESS;
}

size_t ajdarbekov::readLine(size_t &size, size_t &capacity, char *&str1)
{
  int ch = 0;

  while ((ch = std::cin.get()) != '\n' && ch != EOF)
  {
    if (size + 1 >= capacity)
    {
      capacity *= 2;
      char *const term = static_cast< char * >(std::realloc(str1, capacity));
      if (!term)
      {
        return READLINE_ERROR;
      }
      str1 = term;
    }
    str1[size++] = static_cast< char >(ch);
  }
  str1[size] = '\0';
  return size;
}

char *ajdarbekov::getuniquechars(char *buffer, const char *str1,
                                 const char *str2)
{
  size_t sizebuffer = 0;

  for (size_t i = 0; str2[i] != '\0'; ++i)
  {
    int flag1 = 0;
    for (size_t j = 0; str1[j] != '\0'; ++j)
    {
      if (str1[j] == str2[i])
      {
        flag1 = 1;
        break;
      }
    }

    if (flag1 == 0)
    {
      int flag2 = 0;
      for (size_t k = 0; k < sizebuffer; ++k)
      {
        if (buffer[k] == str2[i])
        {
          flag2 = 1;
          break;
        }
      }

      if (flag2 == 0)
      {
        buffer[sizebuffer++] = str2[i];
      }
    }
  }

  for (size_t i = 0; str1[i] != '\0'; ++i)
  {
    int flag1 = 0;
    for (size_t j = 0; str2[j] != '\0'; ++j)
    {
      if (str2[j] == str1[i])
      {
        flag1 = 1;
        break;
      }
    }

    if (flag1 == 0)
    {
      int flag2 = 0;
      for (size_t k = 0; k < sizebuffer; ++k)
      {
        if (buffer[k] == str1[i])
        {
          flag2 = 1;
          break;
        }
      }

      if (flag2 == 0)
      {
        buffer[sizebuffer++] = str2[i];
      }
    }
  }

  buffer[sizebuffer] = '\0';
  return buffer;
}
