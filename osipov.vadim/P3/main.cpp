#include <cstring>
#include <fstream>
#include <iostream>
int const matrix_size = 100;
void obrabotkamatric(int martix[][matrix_size], int rows, int cols);
void obrabotkamatricdynamic(int *matrix, int rows, int cols);

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  }
  if(!(argv[1][0] >= '0' && argv[1][0] <= '9')) {
    std::cerr << "First parameter is not a number" << "\n";
    return 1;
  }
  if (argv[1][0] != '1' && argv[1][0] != '2') {
    std::cerr << "First parameter if out of range" << "\n";
    return 1;
  }
  int matrix[matrix_size][matrix_size];
  int rows = 0;
  int cols = 0;
  std::ifstream fin(argv[2]);
  if (!(fin >> rows >> cols)) {
    if (fin.eof()) {
      std::cerr << "Input file is empty" << "\n";
      return 2;
    } else {
      std::cerr << "Invalid input format" << "\n";
      return 2;
    }
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (!(fin >> matrix[i][j])) {
        std::cerr << "Invalid matrix size" << "\n";
        return 2;
      }
    }
  }
  if (std::strcmp(argv[1], "1") == 0) {
    obrabotkamatric(matrix, rows, cols);
    std::ofstream fout(argv[3]);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        fout << matrix[i][j] << " ";
      }
      fout << "\n";
    }
  } else {
    int *const dynamic_matrix = new int[rows * cols];
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {

        dynamic_matrix[i * cols + j] = matrix[i][j];
      }
    }
    obrabotkamatricdynamic(dynamic_matrix, rows, cols);
    std::ofstream fout(argv[3]);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        fout << dynamic_matrix[(i * cols) + j] << " ";
      }
      fout << "\n";
    }
    delete[] dynamic_matrix;
  }
  return 0;
}
void obrabotkamatric(int matrix[][matrix_size], int rows, int cols) {
  int j = 0;
  int k = 0;

  while (k < rows && k < cols) {

    for (int i = k; i < cols - k; ++i) {
      matrix[rows - 1 - k][i] = matrix[rows - 1 - k][i] + j;
      j = j + 1;
    }

    for (int i = rows - 2 - k; i >= k; --i) {
      matrix[i][cols - 1 - k] = matrix[i][cols - 1 - k] + j;
      j = j + 1;
    }

    if (k < rows - 1 - k) {
      for (int i = cols - 2 - k; i >= k; --i) {
        matrix[k][i] = matrix[k][i] + j;
        j = j + 1;
      }
    }

    if (k < cols - 1 - k) {
      for (int i = k + 1; i < rows - 1 - k; ++i) {
        matrix[i][k] = matrix[i][k] + j;
        j = j + 1;
      }
    }

    k = k + 1;
  }
}
void obrabotkamatricdynamic(int *matrix, int rows, int cols) {
  int j = 0;
  int k = 0;

  while (k < rows && k < cols) {

    for (int i = k; i < cols - k; ++i) {
      matrix[(rows - 1 - k) * cols + i] = matrix[(rows - 1 - k) * cols + i] + j;
      j = j + 1;
    }

    for (int i = rows - 2 - k; i >= k; --i) {
      matrix[(i * cols) + cols - 1 - k] = matrix[(i * cols) + cols - 1 - k] + j;
      j = j + 1;
    }

    if (k < rows - 1 - k) {
      for (int i = cols - 2 - k; i >= k; --i) {
        matrix[(k * cols) + i] = matrix[(k * cols) + i] + j;
        j = j + 1;
      }
    }

    if (k < cols - 1 - k) {
      for (int i = k + 1; i < rows - 1 - k; ++i) {
        matrix[(i * cols) + k] = matrix[(i * cols) + k] + j;
        j = j + 1;
      }
    }

    k = k + 1;
  }
}
