#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

namespace grekova {
  const int MAX_SIZE_ARR = 10000;
  const std::string INV_VAL = "Invalid matrix data";
  const std::string INC_NUM_OF_ARG = "Incorrect number of arguments";
  const std::string INC_NUM = "Incorrect task number";
  const std::string FILE_ERR = "File error";

  void getStaticMatrix(std::ifstream &input, int row, int col, int *out_buffer);
  void getDynamicMatrix(std::ifstream &input, int row, int col, int **&matrix);
  void processSpiral(int **matrix, int rows, int cols);
  void writeMatrixToFile(const std::string &filename, int **matrix, int rows, int cols);
  void freeMatrix(int **matrix, int rows, int mode);
}

int main(int argc, char *argv[])
{
  try {
    if (argc != 4) {
      throw std::invalid_argument(grekova::INC_NUM_OF_ARG);
    }

    const std::string num = argv[1];
    if (num != "1" && num != "2") {
      throw std::invalid_argument(grekova::INC_NUM);
    }

    const int mode = (num == "1") ? 1 : 2;
    const std::string input_filename = argv[2];
    const std::string output_filename = argv[3];

    std::ifstream fin(input_filename);
    if (!fin.is_open()) {
      throw std::runtime_error(grekova::INV_VAL);
    }

    int rows = 0, cols = 0;
    if (!(fin >> rows >> cols)) {
      throw std::runtime_error(grekova::INV_VAL);
    }

    if (rows < 0 || cols < 0) {
      throw std::runtime_error(grekova::INV_VAL);
    }

    int **matrix = nullptr;

    int static_buffer[grekova::MAX_SIZE_ARR] = {0};

    if (rows == 0 || cols == 0) {
      grekova::writeMatrixToFile(output_filename, nullptr, 0, 0);
      return 0;
    }

    if (mode == 1) {
      if (cols == 0 || rows > grekova::MAX_SIZE_ARR / cols) {
        throw std::runtime_error(grekova::INV_VAL);
      }

      grekova::getStaticMatrix(fin, rows, cols, static_buffer);

      matrix = new int *[rows];
      for (int i = 0; i < rows; ++i) {
        matrix[i] = &static_buffer[i * cols];
      }
    } else {
      grekova::getDynamicMatrix(fin, rows, cols, matrix);
    }

    grekova::processSpiral(matrix, rows, cols);
    grekova::writeMatrixToFile(output_filename, matrix, rows, cols);

    grekova::freeMatrix(matrix, rows, mode);
    return 0;

  } catch (const std::bad_alloc &e) {
    std::cerr << grekova::INV_VAL << std::endl;
    return 2;
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }
}

namespace grekova {
  void getStaticMatrix(std::ifstream &input, int row, int col, int *out_buffer)
  {
    if (row != 0 && col > MAX_SIZE_ARR / row) {
      throw std::runtime_error(INV_VAL);
    }

    int arr[MAX_SIZE_ARR] = {0};

    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (!(input >> arr[i * col + j])) {
          throw std::runtime_error(INV_VAL);
        }
      }
    }

    char c = 0;
    while (input.get(c)) {
      if (!std::isspace(static_cast< unsigned char >(c))) {
        throw std::runtime_error(INV_VAL);
      }
    }

    const int total_elements = row * col;
    for (int i = 0; i < total_elements; ++i) {
      out_buffer[i] = arr[i];
    }
  }

  void getDynamicMatrix(std::ifstream &input, int row, int col, int **&matrix)
  {
    matrix = new int *[row];
    for (int i = 0; i < row; ++i) {
      matrix[i] = new int[col];
    }

    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (!(input >> matrix[i][j])) {
          for (int k = 0; k <= i; ++k) {
            delete[] matrix[k];
          }
          delete[] matrix;
          matrix = nullptr;
          throw std::runtime_error(INV_VAL);
        }
      }
    }

    char c = 0;
    while (input.get(c)) {
      if (!std::isspace(static_cast< unsigned char >(c))) {
        for (int k = 0; k < row; ++k) {
          delete[] matrix[k];
        }
        delete[] matrix;
        matrix = nullptr;
        throw std::runtime_error(INV_VAL);
      }
    }
  }

  void processSpiral(int **matrix, int rows, int cols)
  {
    if (rows <= 0 || cols <= 0) {
      return;
    }

    int top = 0, bottom = rows - 1, left = 0, right = cols - 1, increment = 1;

    while (top <= bottom && left <= right) {
      for (int j = left; j <= right; ++j) {
        matrix[bottom][j] += increment++;
      }
      bottom--;

      for (int i = bottom; i >= top; --i) {
        matrix[i][right] += increment++;
      }
      right--;

      if (top <= bottom) {
        for (int j = right; j >= left; --j) {
          matrix[top][j] += increment++;
        }
        top++;
      }

      if (left <= right) {
        for (int i = top; i <= bottom; ++i) {
          matrix[i][left] += increment++;
        }
        left++;
      }
    }
  }

  void writeMatrixToFile(const std::string &filename, int **matrix, int rows, int cols)
  {
    std::ofstream fout(filename);

    if (!fout.is_open()) {
      throw std::runtime_error(FILE_ERR);
    }

    fout << rows << " " << cols << " ";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        fout << matrix[i][j] << " ";
      }
    }

    if (!fout.good()) {
      throw std::runtime_error(FILE_ERR);
    }
  }

  void freeMatrix(int **matrix, int rows, int mode)
  {
    if (matrix) {
      if (mode == 2) {
        for (int i = 0; i < rows; ++i) {
          delete[] matrix[i];
        }
      }
      delete[] matrix;
    }
  }
}
