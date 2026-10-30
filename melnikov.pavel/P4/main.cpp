#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>

namespace melnikov
{
  constexpr int EXIT_FAIL_CODE = 1;
  constexpr int EXIT_SUCCESS_CODE = 0;
  constexpr int DUPLICATE_FOUND = 1;
  constexpr int DUPLICATE_NOT_FOUND = 0;
  constexpr std::size_t INITIAL_CAPACITY = 2;

  int increaseLine(char *&, std::size_t &);
  int readLine(char *&, std::size_t &, std::size_t &);
  int findDuplicate(const char *, const char *);
}

int main()
{
  std::size_t size = 0, capacity = melnikov::INITIAL_CAPACITY;
  char *fst_str = static_cast< char * >(std::malloc(capacity));

  if (fst_str == nullptr)
  {
    std::cerr << "Memory allocation error\n";
    return melnikov::EXIT_FAIL_CODE;
  }

  if (melnikov::readLine(fst_str, size, capacity) != melnikov::EXIT_SUCCESS_CODE)
  {
    std::free(fst_str);
    std::cerr << "Input or memory allocation error\n";
    return melnikov::EXIT_FAIL_CODE;
  }

  const int result = melnikov::findDuplicate(fst_str, "abs");
  std::cout << result << '\n';

  std::free(fst_str);

  return melnikov::EXIT_SUCCESS_CODE;
}

namespace melnikov
{
  int increaseLine(char *&str, std::size_t &capacity)
  {
    capacity *= 2;
    char *const temp = static_cast< char * >(std::realloc(str, capacity));
    if (temp == nullptr)
    {
      return EXIT_FAIL_CODE;
    }
    str = temp;
    return EXIT_SUCCESS_CODE;
  }

  int readLine(char *&str, std::size_t &size, std::size_t &capacity)
  {
    int symbol = std::getchar();
    if (symbol == EOF)
    {
      return EXIT_FAIL_CODE;
    }
    while (symbol != '\n' && symbol != EOF)
    {
      if (size + 1 >= capacity)
      {
        if (increaseLine(str, capacity) == EXIT_FAIL_CODE)
        {
          return EXIT_FAIL_CODE;
        }
      }
      str[size] = static_cast< char >(symbol);
      ++size;
      symbol = std::getchar();
    }
    str[size] = '\0';
    return EXIT_SUCCESS_CODE;
  }

  int findDuplicate(const char *fst_str, const char *sec_str)
  {
    std::size_t fst_len = 0, sec_len = 0;
    for (; fst_str[fst_len] != '\0'; ++fst_len)
    {
    }
    for (; sec_str[sec_len] != '\0'; ++sec_len)
    {
    }

    for (std::size_t i = 0; i < fst_len; ++i)
    {
      for (std::size_t j = 0; j < sec_len; ++j)
      {
        if (fst_str[i] == sec_str[j])
        {
          return DUPLICATE_FOUND;
        }
      }
    }
    return DUPLICATE_NOT_FOUND;
  }
}
