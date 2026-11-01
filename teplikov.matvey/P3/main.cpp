#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <climits>

namespace teplikov
{
  const std::string NOT_EN_ARG = "Not enough arguments";
  const std::string TO_MAN_ARG = "Too many arguments";
  const std::string FR_PARAM_OUT_RNG = "First parameter is out of range";
  const std::string FR_PARAM_NOT_NUM = "First parameter is not a number";
  const std::string INV_VAL = "Invalid matrix data";

  constexpr int EXIT_SUCCESS_CODE = 0;
  constexpr int BAD_ARGS = 1;
  constexpr int BAD_DATA = 2;
  constexpr int LEN = 10000;

  int changeStaticArr(std::ifstream &input, std::ofstream &output, int row, int col);
  int changeDynamicArray(std::ifstream &input, std::ofstream &output, int row, int col);
  void increase(int *arr, int row, int col);
}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    std::cerr << teplikov::NOT_EN_ARG << "\n";
    return teplikov::BAD_ARGS;
  }

  if (argc > 4)
  {
    std::cerr << teplikov::TO_MAN_ARG << "\n";
    return teplikov::BAD_ARGS;
  }

  const std::string arg1(argv[1]);
  if (arg1.length() != 1 ||
      !std::isdigit(static_cast<unsigned char>(arg1[0])))
  {
    std::cerr << teplikov::FR_PARAM_NOT_NUM << "\n";
    return teplikov::BAD_ARGS;
  }

  if (arg1 != "1" && arg1 != "2")
  {
    std::cerr << teplikov::FR_PARAM_OUT_RNG << "\n";
    return teplikov::BAD_ARGS;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);

  int row = 0;
  int col = 0;

  if (!input || !output)
  {
    std::cerr << teplikov::INV_VAL << "\n";
    return teplikov::BAD_DATA;
  }

  try
  {
    if (!(input >> row >> col) || row < 0 || col < 0)
    {
      throw std::invalid_argument(teplikov::INV_VAL);
    }
    if (arg1 == "1")
    {
      teplikov::changeStaticArr(input, output, row, col);
    }
    else
    {
      teplikov::changeDynamicArray(input, output, row, col);
    }
  }
  catch (const std::invalid_argument &exspt)
  {
    std::cerr << "Invalid_argument: " << exspt.what() << "\n";
    return teplikov::BAD_DATA;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory allocation failed\n";
    return teplikov::BAD_DATA;
  }

  return teplikov::EXIT_SUCCESS_CODE;
}

namespace teplikov
{
  int changeStaticArr(std::ifstream &input, std::ofstream &output, int row, int col)
  {
    if (row != 0 && col > LEN / row)
    {
      throw std::invalid_argument(INV_VAL);
    }

    int arr[LEN] = {0};

    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        if (!(input >> arr[i * col + j]))
        {
          throw std::invalid_argument(INV_VAL);
        }
      }
    }

    int extra_num = 0;
    if (input >> extra_num)
    {
      throw std::invalid_argument(INV_VAL);
    }

    increase(arr, row, col);

    output << row << " " << col;
    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        output << " " << arr[i * col + j];
      }
    }
    output << "\n";

    return 0;
  }

  int changeDynamicArray(std::ifstream &input, std::ofstream &output, int row, int col)
  {
    if (row < 0 || col < 0 || (col != 0 && row > INT_MAX / col))
    {
      throw std::invalid_argument(INV_VAL);
    }

    if (row == 0 || col == 0)
    {
      output << row << " " << col << "\n";
      return 0;
    }

    int *const arr = new int[row * col]{0};

    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        if (!(input >> arr[i * col + j]))
        {
          delete[] arr;
          throw std::invalid_argument(INV_VAL);
        }
      }
    }

    int extra_num = 0;
    if (input >> extra_num)
    {
      delete[] arr;
      throw std::invalid_argument(INV_VAL);
    }

    increase(arr, row, col);

    output << row << " " << col;
    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        output << " " << arr[i * col + j];
      }
    }
    output << "\n";

    delete[] arr;

    return 0;
  }

  void increase(int *arr, int row, int col)
  {
    for (int i = 0; i < row; ++i)
    {
      for (int j = 0; j < col; ++j)
      {
        const int top = i;
        const int bott = row - 1 - i;
        const int left = j;
        const int right = col - 1 - j;

        const int v_min = (top < bott) ? top : bott;
        const int h_min = (left < right) ? left : right;
        const int min_bord_dst = (v_min < h_min) ? v_min : h_min;

        arr[i * col + j] += (min_bord_dst + 1);
      }
    }
  }
}
