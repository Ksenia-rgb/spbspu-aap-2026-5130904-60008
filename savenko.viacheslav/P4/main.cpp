#include <iostream>
#include <cctype>
#include <cstring>

namespace savenko {
  constexpr size_t INITIAL_BUFFER_CAPACITY = 16;
  constexpr size_t ALPHABET_SIZE = 256;

  int checkDuplicates(const char* str) noexcept;
}

int main()
{
  size_t buffer_capacity = savenko::INITIAL_BUFFER_CAPACITY;
  char* input_buffer = static_cast< char* >(std::malloc(buffer_capacity));

  if (input_buffer == nullptr) {
    std::cerr << "Error: Memory allocation failed." << "\n";
    return 1;
  }

  size_t string_length = 0;
  int input_char = 0;

  while ((input_char = std::cin.get()) != EOF && input_char != '\n') {
    if (string_length + 1 >= buffer_capacity) {
      buffer_capacity *= 2;
      char* const new_buffer = static_cast< char* >(std::realloc(input_buffer, buffer_capacity));

      if (new_buffer == nullptr) {
        std::free(input_buffer);
        std::cerr << "Error: Memory reallocation failed." << "\n";
        return 1;
      }
      input_buffer = new_buffer;
    }
    input_buffer[string_length++] = static_cast< char >(input_char);
  }

  input_buffer[string_length] = '\0';

  if (string_length == 0 && input_char == EOF) {
    std::cerr << "Error: Empty input and EOF reached." << "\n";
    std::free(input_buffer);
    return 1;
  }

  const int result = savenko::checkDuplicates(input_buffer);

  std::cout << result << "\n";

  std::free(input_buffer);

  return 0;
}

int savenko::checkDuplicates(const char* str) noexcept
{
  if (str == nullptr) {
    return 0;
  }

  unsigned char character_flags[ALPHABET_SIZE] = {0};

  for (size_t i = 0; str[i] != '\0'; ++i) {
    const unsigned char current_index = static_cast< unsigned char >(str[i]);

    if (character_flags[current_index] != 0) {
      return 1;
    }

    character_flags[current_index] = 1;
  }

  return 0;
}
