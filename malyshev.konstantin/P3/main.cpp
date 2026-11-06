#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

namespace malyshev {
  const int error_args = 1;
  const int error_data = 2;
  const int max_size = 10000;
  const size_t max_dynamic_size = 2147483647;
  const std::string elements_more_10000 = "elements more 10000";

  int processFixMassive(std::ifstream &ifile, int *matrix, size_t &rows, size_t &cols);
  int processDynamicMassive(std::ifstream &ifile, int *&matrix, size_t &rows, size_t &cols);
  int longSerCols(const int *matrix, size_t rows, size_t cols);
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Invalid arguments count\n";
    return malyshev::error_args;
  }

  const std::string num = argv[1];
  if (num != "1" && num != "2") {
    std::cerr << "Invalid task number\n";
    return malyshev::error_args;
  }

  const std::string input_filename = argv[2];
  const std::string output_filename = argv[3];
  size_t rows = 0;
  size_t cols = 0;
  int res = 0;
  int read_status = 0;
  int static_matrix[malyshev::max_size];
  int *dynamic_matrix = nullptr;

  std::ifstream file(input_filename);
  if (file.fail()) {
    std::cerr << "Cannot open input file\n";
    return malyshev::error_data;
  }

  if (num == "1") {
    read_status = malyshev::processFixMassive(file, static_matrix, rows, cols);
  } else {
    read_status = malyshev::processDynamicMassive(file, dynamic_matrix, rows, cols);
  }
  file.close();

  if (read_status != 0) {
    std::cerr << "Invalid array data or empty file\n";
    if (num == "2" && dynamic_matrix != nullptr) {
      delete[] dynamic_matrix;
      dynamic_matrix = nullptr;
    }
    return read_status;
  }

  const size_t final_rows = rows;
  const size_t final_cols = cols;

  if (num == "1") {
    res = malyshev::longSerCols(static_matrix, final_rows, final_cols);
  } else if (num == "2") {
    res = malyshev::longSerCols(dynamic_matrix, final_rows, final_cols);
  }

  std::ofstream outfile(output_filename);
  if (outfile.fail()) {
    std::cerr << "Cannot open output file\n";
    if (num == "2") {
      delete[] dynamic_matrix;
    }
    return malyshev::error_args;
  }

  outfile << res << "\n";
  outfile.close();

  if (num == "2") {
    delete[] dynamic_matrix;
  }

  return 0;
}

namespace malyshev {
  int processFixMassive(std::ifstream &ifile, int *matrix, size_t &rows, size_t &cols)
  {
    ifile >> rows >> cols;
    if (ifile.fail()) {
      return error_data;
    }
    if (rows == 0 || cols == 0) {
      return 0;
    }

    const size_t total_el = rows * cols;
    if (total_el > static_cast< size_t >(max_size)) {
      std::cerr << elements_more_10000 << "\n";
      return error_data;
    }

    for (size_t i = 0; i < total_el; i++) {
      ifile >> matrix[i];
      if (ifile.fail()) {
        return error_data;
      }
    }

    char extra = 0;
    ifile >> extra;
    if (!ifile.fail()) {
      return error_data;
    }

    return 0;
  }

  int processDynamicMassive(std::ifstream &ifile, int *&matrix, size_t &rows, size_t &cols)
  {
    ifile >> rows >> cols;
    if (ifile.fail()) {
      return error_data;
    }
    if (rows == 0 || cols == 0) {
      matrix = nullptr;
      return 0;
    }

    const size_t total_el = rows * cols;
    if (total_el > max_dynamic_size) {
      return error_data;
    }

    matrix = new int[total_el];
    for (size_t i = 0; i < total_el; i++) {
      ifile >> matrix[i];
      if (ifile.fail()) {
        delete[] matrix;
        matrix = nullptr;
        return error_data;
      }
    }

    char extra = 0;
    ifile >> extra;
    if (!ifile.fail()) {
      delete[] matrix;
      matrix = nullptr;
      return error_data;
    }

    return 0;
  }

  int longSerCols(const int *matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    int max_ser_len = 0;
    int max_cols = 0;

    for (size_t i = 0; i < cols; i++) {
      int current_sers = 1;
      int max_in_col = 1;

      for (size_t j = 1; j < rows; j++) {
        if (matrix[j * cols + i] == matrix[(j - 1) * cols + i]) {
          current_sers++;
        } else {
          current_sers = 1;
        }
        if (current_sers > max_in_col) {
          max_in_col = current_sers;
        }
      }

      if (max_in_col > max_ser_len) {
        max_ser_len = max_in_col;
        max_cols = static_cast< int >(i) + 1;
      }
    }

    return max_cols;
  }
}
