#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cerrno>
#include <string>
#include <stdexcept>
#include <exception>

namespace kovalev
{
  const int ERR_ARGUMENTS = 1;
  const int ERR_DATA = 2;
  const int STATIC_ARR = 1;
  const int DYNAMIC_ARR = 2;
  const int ARGC_COUNT = 4;
  const int MAXSIZE = 10000;
  const int RADIX = 10;
  int countMin(const int* matrix, int rows, int cols);
}

int main(int argc, char* argv[])
{
  if (argc != kovalev::ARGC_COUNT)
  {
    std::cerr << "Wrong number of arguments\n";
    return kovalev::ERR_ARGUMENTS;
  }
  errno = 0;
  char* end = nullptr;
  const long modeValue = std::strtol(argv[1], &end, kovalev::RADIX);
  if (end == argv[1] || *end != '\0' || errno == ERANGE
      || (modeValue != kovalev::STATIC_ARR && modeValue != kovalev::DYNAMIC_ARR))
  {
    std::cerr << "Num must be 1 or 2\n";
    return kovalev::ERR_ARGUMENTS;
  }
  const int mode = static_cast< int >(modeValue);
  try
  {
    int rows = 0;
    int cols = 0;
    std::ifstream input(argv[2]);
    if (!input)
    {
      throw std::runtime_error("Cannot open input file");
    }
    if (!(input >> rows >> cols))
    {
      throw std::runtime_error("Wrong matrix size");
    }
    if (rows < 0 || cols < 0 || ((rows == 0) != (cols == 0)))
    {
      throw std::runtime_error("Rows and Cols must be positive");
    }
    const long long total = static_cast< long long >(rows) * static_cast< long long >(cols);
    if (mode == kovalev::STATIC_ARR && total > kovalev::MAXSIZE)
    {
      throw std::runtime_error("Too many arguments");
    }
    int static_matrix[kovalev::MAXSIZE] = {};
    const bool isDynamic = (mode == kovalev::DYNAMIC_ARR);
    int* const matrix = isDynamic ? new int[total] : static_matrix;
    for (long long i = 0; i < total; i++)
    {
      if (!(input >> matrix[i]))
      {
        if (isDynamic)
        {
          delete[] matrix;
        }
        throw std::runtime_error("Wrong matrix elements");
      }
    }
    std::string extra = "";
    if (input >> extra)
    {
      if (isDynamic)
      {
        delete[] matrix;
      }
      throw std::runtime_error("Extra data in input file");
    }
    const int result = kovalev::countMin(matrix, rows, cols);
    std::ofstream output(argv[3]);
    if (!output)
    {
      if (isDynamic)
      {
        delete[] matrix;
      }
      throw std::runtime_error("Can't open output file");
    }
    if (rows == 0 && cols == 0)
    {
      output << "0 0\n";
    }
    else
    {
      output << result << '\n';
    }
    if (!output)
    {
      if (isDynamic)
      {
        delete[] matrix;
      }
      throw std::runtime_error("Can't write output file");
    }
    if (isDynamic)
    {
      delete[] matrix;
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return kovalev::ERR_DATA;
  }
  return 0;
}

int kovalev::countMin(const int* matrix, int rows, int cols)
{
  int count = 0;
  for (int row = 1; row < rows - 1; row++)
  {
    for (int col = 1; col < cols - 1; col++)
    {
      const int index = row * cols + col;
      const int current = matrix[index];
      bool is_min = true;
      for (int i = -1; i <= 1; i++)
      {
        for (int j = -1; j <= 1; j++)
        {
          if (i == 0 && j == 0)
          {
            continue;
          }
          const int neighborIndex = (row + i) * cols + col + j;
          if (current >= matrix[neighborIndex])
          {
            is_min = false;
          }
        }
      }
      if (is_min)
      {
        count++;
      }
    }
  }
  return count;
}
