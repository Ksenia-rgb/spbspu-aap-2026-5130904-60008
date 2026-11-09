#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

namespace kovalenko {
  constexpr std::size_t kInitialCapacity = 16;
  char* interleave(char* dst, const char* s1, const char* s2) noexcept
  {
    const std::size_t len1 = std::strlen(s1);
    const std::size_t len2 = std::strlen(s2);
    const std::size_t n = (len1 > len2) ? len1 : len2;

    std::size_t j = 0;
    for (std::size_t i = 0; i < n; ++i) {
      if (i < len1) {
        dst[j++] = s1[i];
      }
      if (i < len2) {
        dst[j++] = s2[i];
      }
    }
    dst[j] = '\0';
    return dst;
  }

  char* readLine(std::istream& in)
  {
    const std::size_t maxSize = std::numeric_limits< std::size_t >::max();

    std::size_t capacity = kInitialCapacity;
    std::size_t size = 0;

    char* data = new char[capacity];

    char ch = '\0';
    bool got_any = false;
    while (in.get(ch)) {
      got_any = true;
      if (ch == '\n') {
        break;
      }
      if (size == capacity - 1) {
        if (capacity > maxSize / 2) {
          delete[] data;
          throw std::length_error("input line too long");
        }

        const std::size_t newCapacity = capacity * 2;
        char* expanded = nullptr;
        try {
          expanded = new char[newCapacity];
        } catch (...) {
          delete[] data;
          throw;
        }

        for (std::size_t k = 0; k < size; ++k) {
          expanded[k] = data[k];
        }

        delete[] data;
        data = expanded;
        capacity = newCapacity;
      }

      data[size++] = ch;
    }

    if (in.bad()) {
      delete[] data;
      throw std::runtime_error("input stream failure");
    }
    if (!got_any) {
      delete[] data;
      throw std::runtime_error("no input data");
    }
    data[size] = '\0';
    return data;
  }

  std::size_t calcOutputSize(std::size_t len1, std::size_t len2)
  {
    const std::size_t maxSize = std::numeric_limits< std::size_t >::max();

    if (len1 > maxSize - len2) {
      throw std::length_error("output size overflow (sum)");
    }
    const std::size_t total = len1 + len2;

    if (total == maxSize) {
      throw std::length_error("output size overflow (+1)");
    }
    return total + 1;
  }

  void run()
  {
    const char* const kSecond = "def_";

    char* source = nullptr;
    char* result = nullptr;

    try {
      source = readLine(std::cin);
      const std::size_t len1 = std::strlen(source);
      const std::size_t len2 = std::strlen(kSecond);

      const std::size_t dstSize = calcOutputSize(len1, len2);
      result = new char[dstSize];

      interleave(result, source, kSecond);

      std::cout << result << '\n';

      delete[] result;
      delete[] source;
    } catch (...) {
      delete[] result;
      delete[] source;
      throw;
    }
  }
}
int main()
{
  try {
    kovalenko::run();
  } catch (const std::bad_alloc&) {
    std::cerr << "Not enough memory\n";
    return 1;
  } catch (const std::length_error& e) {
    std::cerr << "Length error: " << e.what() << '\n';
    return 1;
  } catch (const std::runtime_error& e) {
    std::cerr << "Runtime error: " << e.what() << '\n';
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "Unknown error\n";
    return 1;
  }
  return 0;
}
