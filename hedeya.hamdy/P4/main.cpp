#ifndef MAIN_CPP
#define MAIN_CPP

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace hedeya {
  const std::size_t MAXIMUM_STRING_LENGTH = 10000;

  void printCommonCharacters(char string_1[], char string_2[]);
  int getIndexOfCharacter(const char arr[], char target);
}

int main()
{
  char string_1[hedeya::MAXIMUM_STRING_LENGTH] = "abcd";
  char string_2[hedeya::MAXIMUM_STRING_LENGTH] = "abcdef";

  hedeya::printCommonCharacters(string_1, string_2);

  return EXIT_SUCCESS;
}

namespace hedeya {
  void printCommonCharacters(char string_1[], char string_2[])
  {
    char seen[hedeya::MAXIMUM_STRING_LENGTH];
    char common[hedeya::MAXIMUM_STRING_LENGTH] = {};

    const char* shortest_string = string_1;
    const char* longest_string = string_2;

    if (strlen(string_2) < strlen(string_1)) {
      shortest_string = string_2;
      longest_string = string_1;
    }

    strcpy(seen, shortest_string);  // NOLINT(clang-diagnostic-deprecated-declarations)

    for (int i = 0; i < strlen(longest_string); ++i) {
      const char current_character = longest_string[i];
      const int seen_index = getIndexOfCharacter(seen, current_character);

      if (seen_index != -1) {
        common[i] = current_character;
      }
    }

    std::cout << common;
  }

  int getIndexOfCharacter(const char arr[hedeya::MAXIMUM_STRING_LENGTH], char target)
  {
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
      if (arr[i] == target) {
        return i;
      }
    }
    return -1;
  }
}

#endif
