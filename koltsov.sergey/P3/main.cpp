#include <climits>
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace koltsov
{
  const std::string ERR_ARGS = "Incorrect number of arguments";
  const std::string ERR_TASK_NUM = "Incorrect task number";
  const std::string ERR_OPEN_FILE = "Cannot open file";
  const std::string ERR_MATRIX = "Invalid matrix data";

  const int EXIT_SUCCESS_CODE = 0;
  const int BAD_ARGS = 1;
  const int BAD_DATA = 2;
  const int LENGTH = 10000;

  int parseTask(const std::string& raw);
  int parseInteger(const std::string& token);
  void readMatrix(std::ifstream& input, int* data, int rows, int cols);
  int countSaddlesElements(const int* data, int rows, int cols);
  int runStaticArr(std::ifstream& input, int rows, int cols);
  int runDynamicArr(std::ifstream& input, int rows, int cols);
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << koltsov::ERR_ARGS << "\n";
    return koltsov::BAD_ARGS;
  }

  try
  {
    const int variant = koltsov::parseTask(argv[1]);

    std::ifstream input(argv[2]);
    std::ofstream output(argv[3]);

    if (!input.is_open() || !output.is_open())
    {
      throw std::runtime_error(koltsov::ERR_OPEN_FILE);
    }

    int rows = 0;
    int cols = 0;
    std::string row_token;
    std::string col_token;

    if (!(input >> row_token) || !(input >> col_token))
    {
      throw std::runtime_error(koltsov::ERR_MATRIX);
    }

    rows = koltsov::parseInteger(row_token);
    cols = koltsov::parseInteger(col_token);

    if (rows < 0 || cols < 0)
    {
      throw std::runtime_error(koltsov::ERR_MATRIX);
    }

    int answer = 0;

    if (variant == 1)
    {
      answer = koltsov::runStaticArr(input, rows, cols);
    }
    else if (variant == 2)
    {
      answer = koltsov::runDynamicArr(input, rows, cols);
    }

    output << answer << "\n";
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return koltsov::BAD_ARGS;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return koltsov::BAD_DATA;
  }

  return koltsov::EXIT_SUCCESS_CODE;
}

int koltsov::parseTask(const std::string& raw)
{
  int value = 0;

  try
  {
    std::size_t used = 0;
    value = std::stoi(raw, &used);

    if (used != raw.size() || (value != 1 && value != 2))
    {
      throw std::invalid_argument(ERR_TASK_NUM);
    }
  }
  catch (const std::invalid_argument&)
  {
    throw std::invalid_argument(ERR_TASK_NUM);
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument(ERR_TASK_NUM);
  }

  return value;
}

int koltsov::parseInteger(const std::string& token)
{
  try
  {
    std::size_t used = 0;
    const int value = std::stoi(token, &used);

    if (used != token.size())
    {
      throw std::runtime_error(ERR_MATRIX);
    }

    return value;
  }
  catch (const std::exception&)
  {
    throw std::runtime_error(ERR_MATRIX);
  }
}

void koltsov::readMatrix(std::ifstream& input, int* data, int rows, int cols)
{
  std::string token;

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (!(input >> token))
      {
        throw std::runtime_error(ERR_MATRIX);
      }

      data[i * cols + j] = parseInteger(token);
    }
  }

  if (input >> token)
  {
    throw std::runtime_error(ERR_MATRIX);
  }
}

int koltsov::countSaddlesElements(const int* data, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    return 0;
  }

  int total = 0;

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      const int element = data[i * cols + j];
      bool min_row = true;
      bool max_col = true;

      for (int k = 0; k < cols; ++k)
      {
        if (data[i * cols + k] < element)
        {
          min_row = false;
          break;
        }
      }

      if (!min_row)
      {
        continue;
      }

      for (int k = 0; k < rows; ++k)
      {
        if (data[k * cols + j] > element)
        {
          max_col = false;
          break;
        }
      }

      if (min_row && max_col)
      {
        ++total;
      }
    }
  }

  return total;
}

int koltsov::runStaticArr(std::ifstream& input, int rows, int cols)
{
  if (rows != 0 && cols > LENGTH / rows)
  {
    throw std::runtime_error(ERR_MATRIX);
  }

  int data[LENGTH] = {};

  readMatrix(input, data, rows, cols);

  return countSaddlesElements(data, rows, cols);
}

int koltsov::runDynamicArr(std::ifstream& input, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    std::string extra;
    if (input >> extra)
    {
      throw std::runtime_error(ERR_MATRIX);
    }
    return 0;
  }

  if (rows > INT_MAX / cols)
  {
    throw std::runtime_error(ERR_MATRIX);
  }

  int* const data = new int[rows * cols]();

  try
  {
    readMatrix(input, data, rows, cols);
  }
  catch (...)
  {
    delete[] data;
    throw;
  }

  const int result = countSaddlesElements(data, rows, cols);

  delete[] data;

  return result;
}
