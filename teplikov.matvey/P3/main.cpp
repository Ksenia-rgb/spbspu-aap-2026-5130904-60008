#include <algorithm>
#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>

namespace teplikov
{
  const std::string NOT_EN_ARG = "Not enough arguments";
  const std::string TO_MAN_ARG = "Too many arguments";
  const std::string FR_PARAM_OUT_RNG = "First parameter is out of range";
  const std::string FR_PARAM_NOT_NUM = "First parameter is not a number";
  const std::string INV_VAL = "Invalid matrix data";
  const std::string CANT_OPEN = "Cannot open file";
  const std::string STATIC_MODE = "1";
  const std::string DYNAMIC_MODE = "2";

  constexpr int EXIT_SUCCESS_CODE = 0;
  constexpr int BAD_ARGS = 1;
  constexpr int BAD_DATA = 2;
  constexpr int LEN = 10000;
  constexpr int ARGS_COUNT = 4;
  constexpr int MODE_IDX = 1;
  constexpr int INPUT_IDX = 2;
  constexpr int OUTPUT_IDX = 3;
  constexpr char SEPARATOR = ' ';

  void changeStaticArr(std::istream &input, std::ostream &output, int row, int col);
  void changeDynamicArray(std::istream &input, std::ostream &output, int row, int col);
  void readMatrix(std::istream &input, int *arr, int size);
  void writeMatrix(std::ostream &output, const int *arr, int row, int col);
  void increase(int *arr, int row, int col);
}

int main(int argc, char *argv[])
{
  if (argc < teplikov::ARGS_COUNT)
  {
    std::cerr << teplikov::NOT_EN_ARG << "\n";
    return teplikov::BAD_ARGS;
  }

  if (argc > teplikov::ARGS_COUNT)
  {
    std::cerr << teplikov::TO_MAN_ARG << "\n";
    return teplikov::BAD_ARGS;
  }

  const std::string mode(argv[teplikov::MODE_IDX]);

  if (mode.length() != 1 || !std::isdigit(static_cast< unsigned char >(mode[0])))
  {
    std::cerr << teplikov::FR_PARAM_NOT_NUM << "\n";
    return teplikov::BAD_ARGS;
  }

  if (mode != teplikov::STATIC_MODE && mode != teplikov::DYNAMIC_MODE)
  {
    std::cerr << teplikov::FR_PARAM_OUT_RNG << "\n";
    return teplikov::BAD_ARGS;
  }

  std::ifstream input(argv[teplikov::INPUT_IDX]);
  std::ofstream output(argv[teplikov::OUTPUT_IDX]);

  if (!input || !output)
  {
    std::cerr << teplikov::CANT_OPEN << "\n";
    return teplikov::BAD_DATA;
  }

  try
  {
    int row = 0;
    int col = 0;

    if (!(input >> row >> col) || row < 0 || col < 0)
    {
      throw std::invalid_argument(teplikov::INV_VAL);
    }

    if (mode == teplikov::STATIC_MODE)
    {
      teplikov::changeStaticArr(input, output, row, col);
    }
    else
    {
      teplikov::changeDynamicArray(input, output, row, col);
    }
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << "Invalid_argument: " << error.what() << "\n";
    return teplikov::BAD_DATA;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory allocation failed\n";
    return teplikov::BAD_DATA;
  }

  return teplikov::EXIT_SUCCESS_CODE;
}

void teplikov::changeStaticArr(std::istream &input, std::ostream &output, int row, int col)
{
  if (row != 0 && col > LEN / row)
  {
    throw std::invalid_argument(INV_VAL);
  }

  int arr[LEN] = {0};

  readMatrix(input, arr, row * col);
  increase(arr, row, col);
  writeMatrix(output, arr, row, col);
}

void teplikov::changeDynamicArray(std::istream &input, std::ostream &output, int row, int col)
{
  if (col != 0 && row > INT_MAX / col)
  {
    throw std::invalid_argument(INV_VAL);
  }

  if (row == 0 || col == 0)
  {
    writeMatrix(output, nullptr, row, col);
    return;
  }

  const int size = row * col;
  const std::unique_ptr< int[] > arr = std::make_unique< int[] >(size);

  readMatrix(input, arr.get(), size);
  increase(arr.get(), row, col);
  writeMatrix(output, arr.get(), row, col);
}

void teplikov::readMatrix(std::istream &input, int *arr, int size)
{
  for (int i = 0; i < size; ++i)
  {
    if (!(input >> arr[i]))
    {
      throw std::invalid_argument(INV_VAL);
    }
  }

  int extra_num = 0;
  if (input >> extra_num)
  {
    throw std::invalid_argument(INV_VAL);
  }
}

void teplikov::writeMatrix(std::ostream &output, const int *arr, int row, int col)
{
  output << row << SEPARATOR << col;

  const int size = row * col;
  for (int i = 0; i < size; ++i)
  {
    output << SEPARATOR << arr[i];
  }

  output << "\n";
}

void teplikov::increase(int *arr, int row, int col)
{
  for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
      const int border_distance = std::min({i, row - 1 - i, j, col - 1 - j});
      arr[i * col + j] += border_distance + 1;
    }
  }
}
