#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>

namespace osipov {

  const int Size_prime = 10000;

  void obrabotkamatric(long long int *matrix, long long int rows, long long int cols);
  void obrabotkamatricdynamic(long long int *matrix, long long int rows, long long int cols);
}

int main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  }

  if (argc > 4) {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  }

  if (!(argv[1][0] >= '0' && argv[1][0] <= '9')) {
    std::cerr << "First parameter is not a number" << "\n";
    return 1;
  }

  if ((argv[1][0] != '1') && (argv[1][0] != '2')) {
    std::cerr << "First parameter if out of range" << "\n";
    return 1;
  }

  if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0) {
    std::cerr << "first parameter incorrect";
    return 1;
  }

  long long int matrix[osipov::Size_prime];
  long long int rows = 0;
  long long int cols = 0;

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

  if (rows < 0 || cols < 0) {
    std::cerr << "invalid size" << "\n";
    return 2;
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      long long int temp = 0;

      if (!(fin >> temp)) {
        std::cerr << "invalid argument" << "\n";
        return 2;
      }

      const int next_char = fin.peek();

      if (next_char != EOF && !std::isspace(next_char)) {
        std::cerr << "invalid element" << "\n";
        return 2;
      }

      matrix[i * cols + j] = temp;
    }
  }

  char test = 0;

  if (fin >> test) {
    std::cerr << "error input" << "\n";
    return 2;
  }

  if (std::strcmp(argv[1], "1") == 0) {
    osipov::obrabotkamatric(matrix, rows, cols);

    std::ofstream fout(argv[3]);

    if (!fout.is_open()) {
      std::cerr << "error opening output file" << "\n";
      return 1;
    }

    fout << rows << " " << cols << "\n";

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        fout << matrix[i * cols + j] << " ";
      }

      fout << "\n";
    }

    fout.close();

    if (fout.fail()) {
      std::cerr << "error output" << "\n";
      return 1;
    }
  } else {
    long long int *const dynamic_matrix = new long long int[rows * cols];

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        dynamic_matrix[i * cols + j] = matrix[i * cols + j];
      }
    }

    osipov::obrabotkamatricdynamic(dynamic_matrix, rows, cols);

    std::ofstream fout(argv[3]);

    if (!fout.is_open()) {
      std::cerr << "error opening output file" << "\n";
      return 1;
    }

    fout << rows << " " << cols << "\n";

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        fout << dynamic_matrix[(i * cols) + j] << " ";
      }

      fout << "\n";
    }

    fout.close();

    if (fout.fail()) {
      std::cerr << "error output" << "\n";
      delete[] dynamic_matrix;
      return 1;
    }

    delete[] dynamic_matrix;
  }

  return 0;
}

namespace osipov {
  void obrabotkamatric(long long int *matrix, long long int rows, long long int cols)
  {
    long long int j = 1;
    int k = 0;

    while (2 * k < rows && 2 * k < cols) {
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


  void obrabotkamatricdynamic(long long int *matrix, long long int rows, long long int cols)
  {
    long long int j = 1;
    int k = 0;

    while (2 * k < rows && 2 * k < cols) {
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
}
