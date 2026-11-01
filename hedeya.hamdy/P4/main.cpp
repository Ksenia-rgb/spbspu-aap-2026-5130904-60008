#ifndef MAIN_CPP
#define MAIN_CPP

#include <stdio.h>

#include <cctype>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <new>

namespace hedeya {
  const std::size_t DEFAULT_CAPACITY = 16;
  const int INPUT_ERROR = 1;
  const int OVERFLOW_ERROR = -2;

  class InvalidInputError: public std::runtime_error {
  public:
    explicit InvalidInputError(const char* message = "Invalid input"):
      std::runtime_error(message)
    {}
  };

  char* handleStringInput(char*& buffer, std::size_t& capacity, std::size_t& length);
  char* getCommonCharacters(const char* string_1, const char* string_2, char* output, char* seen);
  std::size_t getIndexOfCharacter(const char* array, char target);
  void deleteElementAtIndex(char* array, std::size_t index);
}

int main()
{
  std::size_t capacity = hedeya::DEFAULT_CAPACITY;
  std::size_t string_1_length = 0;

  char* string_1 = new (std::nothrow) char[capacity];
  if (!string_1) {
    std::cerr << "Input error: Insufficient dynamic memory available.\n";
    return hedeya::INPUT_ERROR;
  }

  const char* const input_result = hedeya::handleStringInput(string_1, capacity, string_1_length);

  if (!input_result) {
    delete[] string_1;
    std::cerr << "Input error: Insufficient dynamic memory available during resizing.\n";
    return hedeya::INPUT_ERROR;
  }

  try {
    const char string_2[] = "abc ef";
    const std::size_t string_2_length = std::strlen(string_2);
    const std::size_t max_length = (string_1_length < string_2_length) ? string_1_length : string_2_length;

    char* const common_buffer = new (std::nothrow) char[max_length + 1];
    char* const seen_buffer = new (std::nothrow) char[max_length + 1];

    if (!common_buffer || !seen_buffer) {
      delete[] string_1;
      delete[] common_buffer;
      delete[] seen_buffer;
      std::cerr << "Invalid input error: Insufficient dynamic memory available.\n";
      return hedeya::INPUT_ERROR;
    }

    const char* const common = hedeya::getCommonCharacters(string_1, string_2, common_buffer, seen_buffer);

    std::cout << common << "\n";

    delete[] string_1;
    delete[] common_buffer;
    delete[] seen_buffer;
    return EXIT_SUCCESS;

  } catch (const hedeya::InvalidInputError& error) {
    std::cerr << "Invalid input error: " << error.what() << "\n";
    return hedeya::INPUT_ERROR;
  }
}

namespace hedeya {
  char* handleStringInput(char*& buffer, std::size_t& capacity, std::size_t& length)
  {
    length = 0;
    int character = 0;

    while ((character = std::cin.get()) != EOF && character != '\n') {
      if (length + 1 >= capacity) {
        capacity *= 2;

        char* const temp = new (std::nothrow) char[capacity];
        if (!temp) {
          return nullptr;
        }

        std::memcpy(temp, buffer, length);
        delete[] buffer;
        buffer = temp;
      }
      buffer[length++] = static_cast< char >(character);
    }
    buffer[length] = '\0';

    return buffer;
  }

  char* getCommonCharacters(const char* string_1, const char* string_2, char* output, char* seen)
  {
    const std::size_t string_1_length = std::strlen(string_1);
    const std::size_t string_2_length = std::strlen(string_2);

    const char* const shortest_string = (string_1_length < string_2_length) ? string_1 : string_2;
    const char* const longest_string = (string_1_length < string_2_length) ? string_2 : string_1;
    const std::size_t longest_length = (string_1_length > string_2_length) ? string_1_length : string_2_length;

    std::strcpy(seen, shortest_string);

    std::size_t common_index = 0;

    for (std::size_t i = 0; i < longest_length; ++i) {
      const char current_character = longest_string[i];

      if (std::iscntrl(static_cast< unsigned char >(current_character))) {
        continue;
      }

      const std::size_t seen_index = getIndexOfCharacter(seen, current_character);

      if (seen_index != static_cast< std::size_t >(-1)) {
        output[common_index++] = current_character;
        deleteElementAtIndex(seen, seen_index);
      }
    }

    output[common_index] = '\0';
    return output;
  }

  std::size_t getIndexOfCharacter(const char* array, char target)
  {
    const std::size_t length = std::strlen(array);
    for (std::size_t i = 0; i < length; ++i) {
      if (array[i] == target) {
        return i;
      }
    }
    return static_cast< std::size_t >(-1);
  }

  void deleteElementAtIndex(char* array, std::size_t index)
  {
    const std::size_t size = std::strlen(array);
    for (std::size_t i = index; i < size; ++i) {
      array[i] = array[i + 1];
    }
  }
}

#endif
