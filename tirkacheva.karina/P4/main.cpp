#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <new>

namespace tirkacheva {
const int EXIT_SUCCESS_CODE = 0;
const int EXIT_FAIL_CODE = 1;
const int MEMORY_ERROR_CODE = 2;
const std::size_t INITIAL_CAPACITY = 2;

const char *const MEMORY_ERROR = "Cannot allocate memory\n";
const char *const INPUT_ERROR = "Input error\n";

int increaseLine(char *&line, std::size_t &capacity, std::size_t size) {
  if (capacity > std::numeric_limits<std::size_t>::max() / 2) {
    return MEMORY_ERROR_CODE;
  }

  const std::size_t newCapacity = capacity * 2;

  if (size >= newCapacity) {
    return MEMORY_ERROR_CODE;
  }

  char *const new_line = new (std::nothrow) char[newCapacity];

  if (new_line == nullptr) {
    return MEMORY_ERROR_CODE;
  }

  for (std::size_t i = 0; i < size; ++i) {
    new_line[i] = line[i];
  }

  new_line[size] = '\0';

  delete[] line;
  line = new_line;
  capacity = newCapacity;

  return EXIT_SUCCESS_CODE;
}

int readLine(char *&line, std::size_t &size, std::size_t &capacity) {
  size = 0;
  line[0] = '\0';

  char symbol = '\0';

  while (std::cin.get(symbol)) {
    if (symbol == '\n') {
      break;
    }

    if (size >= capacity - 1) {
      const int result = increaseLine(line, capacity, size);

      if (result != EXIT_SUCCESS_CODE) {
        return result;
      }
    }

    line[size] = symbol;
    ++size;
  }

  if (std::cin.bad() || (std::cin.fail() && !std::cin.eof()) ||
      (std::cin.eof() && size == 0)) {
    return EXIT_FAIL_CODE;
  }

  line[size] = '\0';

  return EXIT_SUCCESS_CODE;
}

void transform(const char *src, char *dest, std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    dest[i] =
        static_cast<char>(std::tolower(static_cast<unsigned char>(src[i])));
  }

  dest[size] = '\0';
}
}

int main() {
  std::size_t capacity = tirkacheva::INITIAL_CAPACITY;
  std::size_t size = 0;

  char *src = new (std::nothrow) char[capacity];

  if (src == nullptr) {
    std::cerr << tirkacheva::MEMORY_ERROR;
    return tirkacheva::EXIT_FAIL_CODE;
  }

  const int inputResult = tirkacheva::readLine(src, size, capacity);

  if (inputResult != tirkacheva::EXIT_SUCCESS_CODE) {
    delete[] src;

    if (inputResult == tirkacheva::MEMORY_ERROR_CODE) {
      std::cerr << tirkacheva::MEMORY_ERROR;
    } else {
      std::cerr << tirkacheva::INPUT_ERROR;
    }

    return tirkacheva::EXIT_FAIL_CODE;
  }

  char *const dest = new (std::nothrow) char[capacity];

  if (dest == nullptr) {
    delete[] src;
    std::cerr << tirkacheva::MEMORY_ERROR;
    return tirkacheva::EXIT_FAIL_CODE;
  }

  tirkacheva::transform(src, dest, size);

  std::cout.write(dest, static_cast<std::streamsize>(size));
  std::cout.put('\n');

  delete[] src;
  delete[] dest;

  return tirkacheva::EXIT_SUCCESS_CODE;
}
