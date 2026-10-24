#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace kovalenko {

  struct Config {
    int mode;
    std::string input_path;
    std::string output_path;
  };

  Config parseArguments(int argc, char *argv[])
  {
    if (argc != 4) {
      throw std::invalid_argument("Invalid number of arguments. Usage: ./lab num input output");
    }

    char *end_ptr = nullptr;
    const long num = std::strtol(argv[1], &end_ptr, 10);

    if (end_ptr == argv[1] || *end_ptr != '\0') {
      throw std::invalid_argument("First parametr is not a number");
    }
    if (num != 1 && num != 2) {
      throw std::invalid_argument("First parametr is out of range");
    }

    return Config{static_cast< int >(num), argv[2], argv[3]};
  }

  void readMatrixDimensions(std::ifstream &in, int &rows, int &cols)
  {
    if (!(in >> rows >> cols)) {
      throw std::runtime_error("Cannot read matrix dimesions or file is empty");
    }
    if (rows < 0 || cols < 0) {
      throw std::runtime_error("Matrix dimensions cannot be negative");
    }
  }

  void readMatrixData(std::ifstream &in, int *matrix, int total)
  {
    for (int i = 0; i < total; ++i) {
      if (!(in >> matrix[i])) {
        throw std::runtime_error("Not enough elements in matrix or invalid data");
      }
    }
  }

  int findRowWithLongestSeries(const int *matrix, int rows, int cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    int best_row = 1;
    int max_len = 1;

    for (int i = 0; i < rows; ++i) {
      int current_len = 1;
      for (int j = 1; j < cols; ++j) {
        if (matrix[i * cols + j] == matrix[i * cols + j - 1]) {
          current_len++;
        } else {
          current_len = 1;
        }

        if (current_len > max_len) {
          max_len = current_len;
          best_row = i + 1;
        }
      }
    }
    return best_row;
  }

  void writeResult(const std::string &path, int result)
  {
    std::ofstream out(path);
    if (!out) {
      throw std::runtime_error("Cannot open output file for writing");
    }
    out << result << "\n";
    if (!out) {
      throw std::runtime_error("Failed to writeto output file");
    }
  }

  int runProgram(const Config &config)
  {
    std::ifstream in(config.input_path);
    if (!in) {
      throw std::runtime_error("Cannot open input file");
    }

    int rows = 0, cols = 0;
    readMatrixDimensions(in, rows, cols);

    const int total = rows * cols;
    int result = 0;

    if (config.mode == 1) {
      const int kMaxSize = 10000;
      if (total > kMaxSize) {
        throw std::runtime_error("Matrix is too large for static array");
      }
      int static_matrix[kMaxSize];
      readMatrixData(in, static_matrix, total);
      result = findRowWithLongestSeries(static_matrix, rows, cols);

    } else if (config.mode == 2) {
      int *dynamic_matrix = nullptr;
      try {
        dynamic_matrix = new int[total];
        readMatrixData(in, dynamic_matrix, total);
        result = findRowWithLongestSeries(dynamic_matrix, rows, cols);
      } catch (...) {
        delete[] dynamic_matrix;
        throw;
      }
      delete[] dynamic_matrix;
    }

    writeResult(config.output_path, result);
    return 0;
  }
}

int main(int argc, char *argv[])
{
  try {
    const kovalenko::Config config = kovalenko::parseArguments(argc, argv);
    return kovalenko::runProgram(config);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 2;
  } catch (...) {
    std::cerr << "Unknown error occured" << "\n";
    return 2;
  }
}
