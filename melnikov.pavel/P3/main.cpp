#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

namespace melnikov {
  const std::string INC_NUM_OF_ARG = "Incorrect number of arguments";
  const std::string INC_NUM = "Incorrect task number";
  const std::string INV_VAL = "Invalid matrix data";
  const int INVALID_ARGS_EXIT_CODE = 1;
  const int INVALID_DATA_EXIT_CODE = 2;
  const int MAX_SIZE_ARR = 10000;

  int getFixArray(std::ifstream &input, int, int);
  int getDynamicArray(std::ifstream &input, int, int);
  int countEl(const int *arr, int, int);
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << melnikov::INC_NUM_OF_ARG << "\n";
    return melnikov::INVALID_ARGS_EXIT_CODE;
  }

  if (std::string(argv[1]) != "1" && std::string(argv[1]) != "2") {
    std::cerr << melnikov::INC_NUM << "\n";
    return melnikov::INVALID_ARGS_EXIT_CODE;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);

  if (!input || !output) {
    std::cerr << melnikov::INV_VAL << "\n";
    return melnikov::INVALID_DATA_EXIT_CODE;
  }

  int row = 0, col = 0, res = 0;

  try {
    if (!(input >> row >> col) || row < 0 || col < 0) {
      throw std::invalid_argument(melnikov::INV_VAL);
    }

    if (std::string(argv[1]) == "1") {
      res = melnikov::getFixArray(input, row, col);
    } else {
      res = melnikov::getDynamicArray(input, row, col);
    }

    output << std::to_string(res) << "\n";
  } catch (const std::invalid_argument &ex) {
    std::cerr << "Invalid_argument: " << ex.what() << "\n";
    return melnikov::INVALID_DATA_EXIT_CODE;
  } catch (const std::bad_alloc &) {
    std::cerr << "Memory allocation failed\n";
    return melnikov::INVALID_DATA_EXIT_CODE;
  }

  return EXIT_SUCCESS;
}

namespace melnikov {
  int getFixArray(std::ifstream &input, int row, int col)
  {
    if (row != 0 && col > MAX_SIZE_ARR / row) {
      throw std::invalid_argument(INV_VAL);
    }

    int arr[MAX_SIZE_ARR] = {0};

    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (!(input >> arr[i * col + j])) {
          throw std::invalid_argument(INV_VAL);
        }
      }
    }

    return countEl(arr, row, col);
  }

  int getDynamicArray(std::ifstream &input, int row, int col)
  {
    if (row < 0 || col < 0 || (col != 0 && row > INT_MAX / col)) {
      throw std::invalid_argument(INV_VAL);
    }

    if (row == 0 || col == 0) {
      return 0;
    }

    const int size = row * col;
    int *const arr = new int[size]{0};

    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (!(input >> arr[i * col + j])) {
          delete[] arr;
          throw std::invalid_argument(INV_VAL);
        }
      }
    }

    const int res = countEl(arr, row, col);

    delete[] arr;

    return res;
  }

  int countEl(const int *arr, int row, int col)
  {
    if (row == 0 || col == 0) {
      return 0;
    }

    if (row == 1 && col == 1) {
      throw std::invalid_argument(INV_VAL);
    }

    int res = arr[0];

    for (int sj = 0; sj < col - 1; ++sj) {
      int sum = 0;
      int ci = 0, cj = sj;

      while (ci < row && cj >= 0) {
        sum += arr[ci * col + cj];
        ++ci;
        --cj;
      }

      res = (res > sum ? res : sum);
    }

    for (int si = 1; si < row; ++si) {
      int sum = 0;
      int ci = si, cj = col - 1;

      while (ci < row && cj >= 0) {
        sum += arr[ci * col + cj];
        ++ci;
        --cj;
      }

      res = (res > sum ? res : sum);
    }

    return res;
  }
}

