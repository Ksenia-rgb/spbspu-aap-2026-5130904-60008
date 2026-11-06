#include <iostream>
#include <cctype>
#include <cstddef>

namespace kilyan
{
  const int SUCCESS = 0;
  const int MEMORY_ERROR = 1;
  const size_t DEFAULT_CAPACITY = 16;

  size_t readStream(char*& input_buffer, size_t& current_capacity)
  {
    size_t current_length = 0;
    int input_char = std::cin.get();
    if (input_char == EOF)
    {
      input_buffer[0] = '\0';
      return 0;
    }
    while (input_char != '\n' && input_char != EOF)
    {
      if (current_length + 1 >= current_capacity)
      {
        const size_t next_capacity = current_capacity * 2;
        char* const extended_buffer = new (std::nothrow) char[next_capacity];
        if (extended_buffer == nullptr)
        {
          delete[] input_buffer;
          input_buffer = nullptr;
          return 0;
        }
        for (size_t i = 0; i < current_length; ++i)
        {
          extended_buffer[i] = input_buffer[i];
        }
        delete[] input_buffer;
        input_buffer = extended_buffer;
        current_capacity = next_capacity;
      }
      input_buffer[current_length] = static_cast< char >(input_char);
      current_length++;
      input_char = std::cin.get();
    }
    input_buffer[current_length] = '\0';
    return current_length;
  }

  char* removeExtraSpaces(const char* src, char* dst)
  {
    if (src == nullptr || dst == nullptr)
    {
      return dst;
    }
    const char* reader = src;
    size_t write_pos = 0;
    while (*reader != '\0' && std::isspace(static_cast< unsigned char >(*reader)))
    {
      reader++;
    }
    while (*reader != '\0')
    {
      if (!std::isspace(static_cast< unsigned char >(*reader)))
      {
        dst[write_pos++] = *reader;
      }
      else
      {
        if (write_pos > 0 && !std::isspace(static_cast< unsigned char >(dst[write_pos - 1])))
        {
          dst[write_pos++] = ' ';
        }
      }
      reader++;
    }
    if (write_pos > 0 && std::isspace(static_cast< unsigned char >(dst[write_pos - 1])))
    {
      write_pos--;
    }
    dst[write_pos] = '\0';
    return dst;
  }
}

int main()
{
  size_t initial_capacity = kilyan::DEFAULT_CAPACITY;
  char* src_string = new (std::nothrow) char[initial_capacity];
  if (src_string == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return kilyan::MEMORY_ERROR;
  }
  const size_t final_length = kilyan::readStream(src_string, initial_capacity);
  if (src_string == nullptr)
  {
    std::cerr << "Memory allocation failed during reading\n";
    return kilyan::MEMORY_ERROR;
  }
  char* const clean_string = new (std::nothrow) char[final_length + 1];
  if (clean_string == nullptr)
  {
    delete[] src_string;
    std::cerr << "Memory allocation failed for destination\n";
    return kilyan::MEMORY_ERROR;
  }
  kilyan::removeExtraSpaces(src_string, clean_string);
  std::cout << clean_string << '\n';
  delete[] clean_string;
  delete[] src_string;
  return kilyan::SUCCESS;
}
