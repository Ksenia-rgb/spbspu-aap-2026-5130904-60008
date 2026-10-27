#include <iostream>
#include <fstream>
#include <limits>
#include <cstddef>
#include <new>

namespace dumina
{
  const int fixed_array = 1;
  const int dynamic_array = 2;
  const int max_elements = 10000;

  const char* const error_arguments = "ERROR: INVALID NUMBER OF ARGUMENTS";
  const char* const error_number = "ERROR: FIRST PARAMETER IS NOT A NUMBER";
  const char* const error_range = "ERROR: FIRST PARAMETER IS OUT OF RANGE";
  const char* const error_input = "ERROR: INVALID INPUT FILE";
  const char* const error_output = "ERROR: CANNOT OPEN OUTPUT FILE";
  const char* const error_memory = "ERROR: INVALID MATRIX SIZE";

  constexpr int decimal_base = 10;
  constexpr int exit_success_code = 0;
  constexpr int exit_argument_error = 1;
  constexpr int exit_processing_error = 2;
  constexpr int expected_argument_count = 4;
  constexpr int mode_argument_index = 1;
  constexpr int input_argument_index = 2;
  constexpr int output_argument_index = 3;

  bool parseMode(const char* arg, int& mode);
  bool readDimens(std::ifstream& input, int& rows, int& cols);
  bool readMatrix(std::ifstream& input, int* data, int rows, int cols);

  int countRowsWithoutAdjDuplicates(const int* data, int rows, int cols);
  int processFixedArray(std::ifstream& input, std::ofstream& output);
  int processDynamicArray(std::ifstream& input, std::ofstream& output);
  int run(int argc, char* argv[]);
}

int main(int argc, char* argv[])
{
  return dumina::run(argc, argv);
}

bool dumina::parseMode(const char* arg, int& mode)
{
  if (arg[0] == '\0')
  {
    return false;
  }

  int value = 0;

  for (int i = 0; arg[i] != '\0'; ++i)
  {
    if (arg[i] < '0' || arg[i] > '9')
    {
      return false;
    }

    const int digit = arg[i] - '0';

    if (value > (std::numeric_limits< int >::max() - digit) / decimal_base)
    {
      return false;
    }

    value = value * decimal_base + digit;
  }

  mode = value;
  return true;
}

bool dumina::readDimens(std::ifstream& input, int& rows, int& cols)
{
  if (!(input >> rows >> cols))
  {
    return false;
  }

  if (rows < 0 || cols < 0)
  {
    return false;
  }

  if (rows != 0 && cols > std::numeric_limits< int >::max() / rows)
  {
    return false;
  }

  return true;
}

bool dumina::readMatrix(std::ifstream& input, int* data, int rows, int cols)
{
  const int count = rows * cols;

  for (int i = 0; i < count; ++i)
  {
    if (!(input >> data[i]))
    {
      return false;
    }
  }

  input >> std::ws;

  return input.eof();
}

int dumina::countRowsWithoutAdjDuplicates(const int* data, int rows, int cols)
{
  int result = 0;

  for (int i = 0; i < rows; ++i)
  {
    bool has_adjacent_duplicates = false;

    for (int j = 1; j < cols; ++j)
    {
      if (data[i * cols + j] == data[i * cols + j - 1])
      {
        has_adjacent_duplicates = true;
        break;
      }
    }

    if (!has_adjacent_duplicates)
    {
      ++result;
    }
  }

  return result;
}

int dumina::processFixedArray(std::ifstream& input, std::ofstream& output)
{
  int rows = 0;
  int cols = 0;

  if (!dumina::readDimens(input, rows, cols))
  {
    std::cerr << dumina::error_input << '\n';
    return exit_processing_error;
  }

  if (rows != 0 && cols > dumina::max_elements / rows)
  {
    std::cerr << dumina::error_memory << '\n';
    return exit_processing_error;
  }

  int data[dumina::max_elements] = {};

  if (!dumina::readMatrix(input, data, rows, cols))
  {
    std::cerr << dumina::error_input << '\n';
    return exit_processing_error;
  }

  const int result = dumina::countRowsWithoutAdjDuplicates(data, rows, cols);

  output << result << '\n';

  if (!output)
  {
    return exit_processing_error;
  }

  return 0;
}

int dumina::processDynamicArray(std::ifstream& input, std::ofstream& output)
{
  int rows = 0;
  int cols = 0;

  if (!dumina::readDimens(input, rows, cols))
  {
    std::cerr << dumina::error_input << '\n';
    return exit_processing_error;
  }

  const std::size_t row_count = static_cast< std::size_t >(rows);

  const std::size_t col_count = static_cast< std::size_t >(cols);

  if (col_count != 0 && row_count > std::numeric_limits< std::size_t >::max() / col_count)
  {
    std::cerr << dumina::error_memory << '\n';
    return exit_processing_error;
  }

  const std::size_t count = row_count * col_count;

  if (count > static_cast< std::size_t >(std::numeric_limits< int >::max()))
  {
    std::cerr << dumina::error_memory << '\n';
    return exit_processing_error;
  }

  int* data = nullptr;

  try
  {
    if (count > 0)
    {
      data = new int[count];
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << dumina::error_memory << '\n';
    return exit_processing_error;
  }

  if (!dumina::readMatrix(input, data, rows, cols))
  {
    delete[] data;
    std::cerr << dumina::error_input << '\n';
    return exit_processing_error;
  }

  const int result = dumina::countRowsWithoutAdjDuplicates(data, rows, cols);

  output << result << '\n';

  delete[] data;

  if (!output)
  {
    return exit_processing_error;
  }

  return 0;
}

int dumina::run(int argc, char* argv[])
{
  if (argc != expected_argument_count)
  {
    std::cerr << dumina::error_arguments << '\n';
    return 1;
  }

  int mode = 0;

  if (!dumina::parseMode(argv[mode_argument_index], mode))
  {
    std::cerr << dumina::error_number << '\n';
    return 1;
  }

  if (mode != dumina::fixed_array && mode != dumina::dynamic_array)
  {
    std::cerr << dumina::error_range << '\n';
    return 1;
  }

  std::ifstream input(argv[input_argument_index]);

  if (!input)
  {
    std::cerr << dumina::error_input << '\n';
    return exit_processing_error;
  }

  std::ofstream output(argv[output_argument_index]);

  if (!output)
  {
    std::cerr << dumina::error_output << '\n';
    return exit_processing_error;
  }

  if (mode == dumina::fixed_array)
  {
    return dumina::processFixedArray(input, output);
  }

  return dumina::processDynamicArray(input, output);
}
