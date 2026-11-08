#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>

namespace grekova {
  constexpr int EXIT_ERROR = 1;
  constexpr std::size_t START_CAPACITY = 2;

  int readStr(char *&str, std::size_t &size, std::size_t &capacity);
  int increaseCapacity(char *&str, std::size_t &capacity);
  void findDuplicate(const char *str, char *result);
}

int main()
{
  std::size_t size = 0, capacity = grekova::START_CAPACITY;
  char *str = static_cast<char *>(std::malloc(capacity));

  if (str == nullptr) {
    std::cerr << "Memory allocation error\n";
    return grekova::EXIT_ERROR;
  }

  if (grekova::readStr(str, size, capacity) != EXIT_SUCCESS) {
    std::free(str);
    std::cerr << "Input or memory allocation error\n";
    return grekova::EXIT_ERROR;
  }

  char *const result = static_cast<char *>(std::malloc(size + 1));
  if (result == nullptr) {
    std::free(str);
    std::cerr << "Memory allocation error\n";
    return grekova::EXIT_ERROR;
  }

  grekova::findDuplicate(str, result);

  std::cout << result << '\n';

  std::free(str);
  std::free(result);

  return EXIT_SUCCESS;
}

namespace grekova {
  int increaseCapacity(char *&str, std::size_t &capacity)
  {
    capacity *= 2;
    char *const temp = static_cast<char *>(std::realloc(str, capacity));
    if (temp == nullptr) {
      return EXIT_ERROR;
    }
    str = temp;
    return EXIT_SUCCESS;
  }

  int readStr(char *&str, std::size_t &size, std::size_t &capacity)
  {
    int sym = std::getchar();
    if (sym == EOF) {
      return EXIT_ERROR;
    }
    while (sym != '\n' && sym != EOF) {
      if (size + 1 == capacity) {
        if (increaseCapacity(str, capacity) == EXIT_ERROR) {
          return EXIT_ERROR;
        }
      }
      str[size] = static_cast<char>(sym);
      ++size;
      sym = std::getchar();
    }
    str[size] = '\0';
    return EXIT_SUCCESS;
  }

  void findDuplicate(const char *str, char *result)
  {
    std::size_t len = 0;
    for (; str[len] != '\0'; ++len) {
    }

    std::size_t res_idx = 0;

    for (std::size_t i = 0; i < len; ++i) {
      int count = 0;
      for (std::size_t j = 0; j < len; ++j) {
        if (str[i] == str[j]) {
          ++count;
        }
        if (count > 1) {
          break;
        }
      }

      if (count > 1) {
        bool already_added = false;
        for (std::size_t k = 0; k < res_idx; ++k) {
          if (result[k] == str[i]) {
            already_added = true;
            break;
          }
        }

        if (!already_added) {
          result[res_idx] = str[i];
          ++res_idx;
        }
      }
    }

    result[res_idx] = '\0';
  }
}
