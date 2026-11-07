#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace kiriukhin {
  std::size_t removeLatin(const char *const src, char *const dst) noexcept
  {
    std::size_t count = 0;
    for (std::size_t i = 0; src[i] != '\0'; ++i) {
      if (!std::isalpha(static_cast< unsigned char >(src[i]))) {
        dst[count++] = src[i];
      }
    }
    dst[count] = '\0';
    return count;
  }

  char *readLine()
  {
    const std::size_t initialCapacity = 16;
    const std::size_t growthFactor = 2;
    std::size_t capacity = initialCapacity;
    std::size_t size = 0;
    char *buffer = static_cast< char * >(std::malloc(capacity));
    if (buffer == nullptr) {
      return nullptr;
    }
    int ch = 0;
    while ((ch = std::getchar()) != EOF && ch != '\n') {
      if (size + 1 == capacity) {
        capacity *= growthFactor;
        char *const grown = static_cast< char * >(std::realloc(buffer, capacity));
        if (grown == nullptr) {
          std::free(buffer);
          return nullptr;
        }
        buffer = grown;
      }
      buffer[size++] = static_cast< char >(ch);
    }
    buffer[size] = '\0';
    return buffer;
  }
}

int main()
{
  char *const input = kiriukhin::readLine();
  if (input == nullptr) {
    std::fputs("Error: not enough memory to read the string\n", stderr);
    return 1;
  }

  if (input[0] == '\0') {
    std::free(input);
    std::fputs("Error: empty input\n", stderr);
    return 1;
  }

  char *const result = static_cast< char * >(std::malloc(std::strlen(input) + 1));
  if (result == nullptr) {
    std::free(input);
    std::fputs("Error: not enough memory for the result\n", stderr);
    return 1;
  }

  kiriukhin::removeLatin(input, result);
  std::puts(result);

  std::free(result);
  std::free(input);
  return 0;
}
