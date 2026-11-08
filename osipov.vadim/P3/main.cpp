#include <cstring>
#include <fstream>
#include <iostream>

void obrabotka_matric(int martix[][100], int rows, int cols);
void obrabotka_matric_dynamic(int *matrix, int rows, int cols);

int main(int argc, char *argv[]) {
  if (argc != 4) {
    return 1;
  }
  if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0) {
    return 1;
  }
  int const matrix_size = 100;
  int matrix[matrix_size][matrix_size];
  int rows = 0;
  int cols = 0;
  std::ifstream fin(argv[2]);
  fin >> rows >> cols;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      fin >> matrix[i][j];
    }
  }
  if (std::strcmp(argv[1], "1") == 0) {
    obrabotka_matric(matrix, rows, cols);
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
    obrabotka_matric_dynamic(dynamic_matrix, rows, cols);
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
void obrabotka_matric(int matrix[][100], int rows, int cols) {
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
void obrabotka_matric_dynamic(int *matrix, int rows, int cols) {
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
