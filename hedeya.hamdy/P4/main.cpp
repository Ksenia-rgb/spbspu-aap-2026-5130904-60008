#ifndef MAIN_CPP
#define MAIN_CPP

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace hedeya {
  const std::size_t MAXIMUM_STRING_LENGTH = 10000;

  void printCommonCharacters(char string_1[], char string_2[]);
  long long getIndexOfCharacter(const char arr[hedeya::MAXIMUM_STRING_LENGTH], char target);
  void deleteElementAtIndex(char array[hedeya::MAXIMUM_STRING_LENGTH], std::size_t index);
}

int main()
{
  char string_1[hedeya::MAXIMUM_STRING_LENGTH] = "bc f";
  char string_2[hedeya::MAXIMUM_STRING_LENGTH] = "abc ef";

  hedeya::printCommonCharacters(string_1, string_2);

  return EXIT_SUCCESS;
}

namespace hedeya {
  void printCommonCharacters(char string_1[], char string_2[])
  {
    char seen[hedeya::MAXIMUM_STRING_LENGTH] = {};
    char common[hedeya::MAXIMUM_STRING_LENGTH] = {};

    const char* shortest_string = string_1;
    const char* longest_string = string_2;

    if (strlen(string_2) < strlen(string_1)) {
      shortest_string = string_2;
      longest_string = string_1;
    }

    strcpy(seen, shortest_string);  // NOLINT(clang-diagnostic-deprecated-declarations)

    std::size_t common_index = 0;

    for (std::size_t i = 0; i < strlen(longest_string); ++i) {
      const char current_character = longest_string[i];
      const long long seen_index = getIndexOfCharacter(seen, current_character);

      if (seen_index != -1) {
        common[common_index] = current_character;
        deleteElementAtIndex(seen, seen_index);
        ++common_index;
      }
    }

    std::cout << common;
  }

  long long getIndexOfCharacter(const char array[hedeya::MAXIMUM_STRING_LENGTH], char target)
  {
    std::size_t length = strlen(array);

    for (long long i = 0; i < length; i++) {
      if (array[i] == target) {
        return i;
      }
    }
    return -1;
  }

  void deleteElementAtIndex(char array[hedeya::MAXIMUM_STRING_LENGTH], std::size_t index)
  {
    std::size_t size = strlen(array);

    for (std::size_t i = index; i < size - index; ++i) {
      array[i] = array[i + 1];
    }
  }
}

#endif
