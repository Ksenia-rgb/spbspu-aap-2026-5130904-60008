#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

namespace savenko {
  void readMatrixFromFile(const std::string &input_filename, int *matrix, int max_capacity, int &rows, int &cols);
  void applyLayerIncrement(int *matrix, int rows, int cols);
  void writeMatrixToFile(const std::string &output_filename, const int *matrix, int rows, int cols);

  void processFileWithStaticArray(const std::string &input_filename, const std::string &output_filename);
  void processFileWithDynamicArray(const std::string &input_filename, const std::string &output_filename);
}

int main(const int argc, const char *const argv[])
{
  if (argc != 4) {
    std::cerr << "Error: Invalid number of arguments. Expected: ./lab num input output\n";
    return 1;
  }

  try {
    const std::string parameter_string = argv[1];
    const std::string input_filename = argv[2];
    const std::string output_filename = argv[3];

    if (parameter_string != "1" && parameter_string != "2") {
      std::cerr << "Error: First parameter must be 1 or 2.\n";
      return 1;
    }

    const int parameter = std::stoi(parameter_string);

    if (parameter == 1) {
      savenko::processFileWithStaticArray(input_filename, output_filename);
    } else if (parameter == 2) {
      savenko::processFileWithDynamicArray(input_filename, output_filename);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (int error_code) {
    return error_code;
  }

  return 0;
}

void savenko::readMatrixFromFile(const std::string &input_filename, int *matrix, int max_capacity, int &rows, int &cols)
{
  std::ifstream in_file(input_filename);
  if (!in_file.is_open()) {
    std::cerr << "Error: Failed to open the file for reading!\n";
    throw 2;
  }

  if (!(in_file >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error: Invalid matrix dimensions.\n";
    throw 2;
  }

  const int total_elements = rows * cols;
  if (total_elements > max_capacity) {
    std::cerr << "Error: Matrix exceeds allocated capacity.\n";
    throw 2;
  }

  int element_count = 0;
  int current_number = 0;

  while (in_file >> current_number) {
    if (element_count >= total_elements) {
      std::cerr << "Error: Extraneous elements found.\n";
      throw 2;
    }

    matrix[element_count] = current_number;
    element_count = element_count + 1;
  }

  if (!in_file.eof() && in_file.fail()) {
    std::cerr << "Error: Invalid character or overflow.\n";
    throw 2;
  }

  if (element_count < total_elements) {
    std::cerr << "Error: Not enough elements.\n";
    throw 2;
  }

  in_file.close();
}

void savenko::applyLayerIncrement(int *matrix, int rows, int cols)
{
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      const int dist_top = i;
      const int dist_bottom = rows - 1 - i;
      const int dist_left = j;
      const int dist_right = cols - 1 - j;

      const int layer = std::min({dist_top, dist_bottom, dist_left, dist_right});
      const int index_1d = i * cols + j;

      matrix[index_1d] = matrix[index_1d] + (layer + 1);
    }
  }
}

void savenko::writeMatrixToFile(const std::string &output_filename, const int *matrix, int rows, int cols)
{
  std::ofstream out_file(output_filename);
  if (!out_file.is_open()) {
    std::cerr << "Error: Failed to open file for writing!\n";
    throw 2;
  }

  out_file << rows << " " << cols;

  const int total_elements = rows * cols;
  for (int i = 0; i < total_elements; ++i) {
    out_file << " " << matrix[i];
  }

  out_file << "\n";
  out_file.close();
}

void savenko::processFileWithStaticArray(const std::string &input_filename, const std::string &output_filename)
{
  const int max_elements = 10000;
  int matrix[max_elements] = {};
  int rows = 0;
  int cols = 0;

  readMatrixFromFile(input_filename, matrix, max_elements, rows, cols);
  applyLayerIncrement(matrix, rows, cols);
  writeMatrixToFile(output_filename, matrix, rows, cols);
}

void savenko::processFileWithDynamicArray(const std::string &input_filename, const std::string &output_filename)
{
  int rows = 0;
  int cols = 0;

  {
    std::ifstream in_file(input_filename);
    if (!in_file.is_open() || !(in_file >> rows >> cols) || rows < 0 || cols < 0) {
      std::cerr << "Error: Invalid matrix or dimensions.\n";
      throw 2;
    }
  }

  const int total_elements = rows * cols;
  int *const matrix = new int[total_elements]();

  try {
    int rows_check = 0;
    int cols_check = 0;

    readMatrixFromFile(input_filename, matrix, total_elements, rows_check, cols_check);
    applyLayerIncrement(matrix, rows, cols);
    writeMatrixToFile(output_filename, matrix, rows, cols);
  } catch (int error_code) {
    delete[] matrix;
    throw error_code;
  }

  delete[] matrix;
}
