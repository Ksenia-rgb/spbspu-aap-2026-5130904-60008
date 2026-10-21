#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <new>
#include <string>

namespace grekova {
const int EXIT_SUCCESS_CODE = 0;
const int EXIT_ARGS_ERROR = 1;
const int EXIT_FILE_ERROR = 2;
const int EXIT_MATRIX_ERROR = 2;
const int MAX_SIZE_ARR = 10000;
const std::string INC_NUM_OF_ARG = "Incorrect number of arguments";
const std::string INC_NUM = "Incorrect task number";
const std::string INV_VAL = "Invalid matrix data";

int readMatrix(const std::string &filename, int mode, int **&matrix, int &rows,
               int &cols, int *&static_storage);
void processSpiral(int **matrix, int rows, int cols);
bool readInt(std::ifstream &in, int &val);
void writeMatrixToFile(const std::string &filename, int **matrix, int rows,
                       int cols);
}

int main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cerr << grekova::INC_NUM_OF_ARG << "\n";
    return grekova::EXIT_ARGS_ERROR;
  }

  if (argc > 4) {
    std::cerr << grekova::INC_NUM_OF_ARG << "\n";
    return grekova::EXIT_ARGS_ERROR;
  }

  const std::string num = argv[1];

  if (num != "1" && num != "2") {
    bool is_numeric = true;
    for (const char c : num) {
      if (!std::isdigit(c)) {
        is_numeric = false;
        break;
      }
    }

    if (is_numeric) {
      std::cerr << grekova::INC_NUM << "\n";
      return grekova::EXIT_ARGS_ERROR;
    } else {
      std::cerr << grekova::INC_NUM << "\n";
      return grekova::EXIT_ARGS_ERROR;
    }
  }

  const int mode = (num == "1") ? 1 : 2;

  int **matrix = nullptr;
  int *static_storage = nullptr;
  int rows = 0, cols = 0;

  const int read_status =
      grekova::readMatrix(argv[2], mode, matrix, rows, cols, static_storage);
  if (read_status != grekova::EXIT_SUCCESS_CODE) {
    return read_status;
  }

  if (rows == 0 && cols == 0) {
    grekova::writeMatrixToFile(argv[3], nullptr, 0, 0);
    return grekova::EXIT_SUCCESS_CODE;
  }

  grekova::processSpiral(matrix, rows, cols);

  grekova::writeMatrixToFile(argv[3], matrix, rows, cols);

  if (mode == 1) {
    delete[] matrix;
    delete[] static_storage;
  } else {
    delete[] matrix;
  }

  return grekova::EXIT_SUCCESS_CODE;
}

bool grekova::readInt(std::ifstream &in, int &val) {
  return static_cast<bool>(in >> val);
}

int grekova::readMatrix(const std::string &filename, int mode, int **&matrix,
                        int &rows, int &cols, int *&static_storage) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << grekova::INV_VAL << "\n";
    return EXIT_MATRIX_ERROR;
  }

  if (!readInt(fin, rows) || !readInt(fin, cols)) {
    std::cerr << grekova::INV_VAL << "\n";
    return EXIT_MATRIX_ERROR;
  }

  if (rows < 0 || cols < 0) {
    std::cerr << grekova::INV_VAL << "\n";
    return EXIT_MATRIX_ERROR;
  }

  if (rows == 0 && cols == 0) {
    matrix = nullptr;
    return EXIT_SUCCESS_CODE;
  }

  if (mode == 1) {
    if (rows * cols > MAX_SIZE_ARR) {
      std::cerr << grekova::INV_VAL << "\n";
      return EXIT_MATRIX_ERROR;
    }

    static_storage = new int[grekova::MAX_SIZE_ARR];
    matrix = new int *[rows];

    int idx = 0, val = 0;
    for (int i = 0; i < rows; ++i) {
      matrix[i] = &static_storage[i * cols];
      for (int j = 0; j < cols; ++j) {
        if (!readInt(fin, val)) {
          std::cerr << grekova::INV_VAL << "\n";
          delete[] static_storage;
          delete[] matrix;
          return EXIT_MATRIX_ERROR;
        }
        static_storage[idx++] = val;
      }
    }
  } else {
    try {
      matrix = new int *[rows];
      for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
      }
    } catch (const std::bad_alloc &e) {
      std::cerr << grekova::INV_VAL << "\n";
      if (matrix) {
        for (int i = 0; i < rows; ++i)
          delete[] matrix[i];
        delete[] matrix;
      }
      return EXIT_FILE_ERROR;
    }

    int val = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!readInt(fin, val)) {
          std::cerr << grekova::INV_VAL << "\n";
          for (int k = 0; k < rows; ++k)
            delete[] matrix[k];
          delete[] matrix;
          return EXIT_MATRIX_ERROR;
        }
        matrix[i][j] = val;
      }
    }
  }
  return EXIT_SUCCESS_CODE;
}

void grekova::processSpiral(int **matrix, int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    return;

  int top = 0, bottom = rows - 1, left = 0, right = cols - 1, increment = 1;

  while (top <= bottom && left <= right) {

    for (int j = left; j <= right; ++j)
      matrix[bottom][j] += increment++;
    bottom--;

    for (int i = bottom; i >= top; --i)
      matrix[i][right] += increment++;
    right--;

    if (top <= bottom) {
      for (int j = right; j >= left; --j)
        matrix[top][j] += increment++;
      top++;
    }

    if (left <= right) {
      for (int i = top; i <= bottom; ++i)
        matrix[i][left] += increment++;
      left++;
    }
  }
}

void grekova::writeMatrixToFile(const std::string &filename, int **matrix,
                                int rows, int cols) {
  std::ofstream fout(filename);
  if (!fout.is_open()) {
    std::cerr << grekova::INV_VAL << "\n";
    return;
  }

  fout << rows << " " << cols << " ";
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      fout << matrix[i][j] << " ";
    }
  }
}
