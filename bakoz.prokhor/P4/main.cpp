#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace bakoz
{
  constexpr int         SUCCESS_CODE = 0;
  constexpr int         ERR_CODE = 1;
  constexpr int         SEQUENCE_FOUND = 1;
  constexpr int         SEQUENCE_NOT_FOUND = 0;
  constexpr std::size_t INIT_BUF = 2;

  int readLine(char *&buffer, std::size_t &length, std::size_t &cap);
  int expandBuffer(char *&buffer, std::size_t &cap);
  int hasRepeatChars(const char *str);
} // namespace bakoz

int main()
{
  std::size_t length = 0;
  std::size_t cap = bakoz::INIT_BUF;
  char       *line = static_cast<char *>(std::malloc(cap));

  if (line == nullptr)
  {
    std::cerr << "memory allocation error" << "\n";
    return bakoz::ERR_CODE;
  }

  if (bakoz::readLine(line, length, cap) != bakoz::SUCCESS_CODE)
  {
    std::free(line);
    std::cerr << "input error" << "\n";
    return bakoz::ERR_CODE;
  }

  const int result = bakoz::hasRepeatChars(line);
  std::cout << result << "\n";

  std::free(line);

  return bakoz::SUCCESS_CODE;
}

int bakoz::expandBuffer(char *&buffer, std::size_t &cap)
{
  cap *= 2;
  char *const tmp = static_cast<char *>(std::realloc(buffer, cap));
  if (tmp == nullptr)
  {
    return ERR_CODE;
  }
  buffer = tmp;
  return SUCCESS_CODE;
}

int bakoz::readLine(char *&buffer, std::size_t &length, std::size_t &cap)
{
  int ch = std::getchar();
  if (ch == EOF)
  {
    return ERR_CODE;
  }
  while ((ch != '\n') && (ch != EOF))
  {
    if ((length + 1) >= cap)
    {
      if (expandBuffer(buffer, cap) == ERR_CODE)
      {
        return ERR_CODE;
      }
    }
    buffer[length] = static_cast<char>(ch);
    ++length;
    ch = std::getchar();
  }
  buffer[length] = '\0';
  return SUCCESS_CODE;
}

int bakoz::hasRepeatChars(const char *str)
{
  if (str == nullptr)
  {
    return SEQUENCE_NOT_FOUND;
  }

  for (std::size_t i = 0; str[i] != '\0' && str[i + 1] != '\0'; ++i)
  {
    if (str[i] == str[i + 1])
    {
      return SEQUENCE_FOUND;
    }
  }
  return SEQUENCE_NOT_FOUND;
}
