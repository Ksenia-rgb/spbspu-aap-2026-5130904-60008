#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace inashevskiy {
const int EXIT_CODE_SUCCESS = 0;
const int EXIT_CODE_FAIL = 1;
const size_t EXIT_CODE_FAIL_READLINE = -1;
const char *const str2 = "abc_ef";

char *getuniquechars(char *, const char *, const char *);
size_t readLine(size_t &, size_t &, char *&);
}

int main() {
  const size_t INITIAL_CAPACITY = 16;
  size_t capacity = INITIAL_CAPACITY;
  size_t size = 0;

  char *str1 = static_cast<char *>(std::malloc(capacity));
  if (!str1) {
    std::cerr << "Memory allocation error";
    return inashevskiy::EXIT_CODE_FAIL;
  }

  size = inashevskiy::readLine(size, capacity, str1);
  if (size == inashevskiy::EXIT_CODE_FAIL_READLINE) {
    std::free(str1);
    std::cerr << "Memory allocation error";
    return inashevskiy::EXIT_CODE_FAIL;
  }

  const size_t result_capacity = size + std::strlen(inashevskiy::str2) + 1;

  char *buffer = static_cast<char *>(std::malloc(result_capacity));

  if (!buffer) {
    std::free(str1);
    std::cerr << "Memory allocation error";
    return inashevskiy::EXIT_CODE_FAIL;
  }

  buffer = inashevskiy::getuniquechars(buffer, str1, inashevskiy::str2);

  std::cout << buffer << '\n';

  std::free(str1);
  std::free(buffer);

  return inashevskiy::EXIT_CODE_SUCCESS;
}

size_t inashevskiy::readLine(size_t &size, size_t &capacity, char *&str1) {
  int ch = 0;

  while ((ch = std::cin.get()) != '\n' && ch != EOF) {
    if (size + 1 >= capacity) {
      capacity *= 2;

      char *const term = static_cast<char *>(std::realloc(str1, capacity));

      if (!term) {
        std::free(str1);
        str1 = nullptr;
        return EXIT_CODE_FAIL_READLINE;
      }

      str1 = term;
    }

    str1[size++] = static_cast<char>(ch);
  }

  if (ch == EOF && size == 0) {
    return EXIT_CODE_FAIL_READLINE;
  }

  str1[size] = '\0';

  return size;
}

char *inashevskiy::getuniquechars(char *buffer, const char *str1,
                                  const char *str2) {
  size_t sizebuffer = 0;

  for (size_t i = 0; str1[i] != '\0'; ++i) {
    const char current = str1[i];

    if (std::isalnum(static_cast<unsigned char>(current)) ||
        std::ispunct(static_cast<unsigned char>(current))) {
      int found = 0;

      for (size_t j = 0; str2[j] != '\0'; ++j) {
        if (current == str2[j]) {
          found = 1;
          break;
        }
      }

      if (found == 1) {
        int repeated = 0;

        for (size_t k = 0; k < sizebuffer; ++k) {
          if (buffer[k] == current) {
            repeated = 1;
            break;
          }
        }

        if (repeated == 0) {
          buffer[sizebuffer++] = current;
        }
      }
    }
  }

  buffer[sizebuffer] = '\0';

  return buffer;
}
