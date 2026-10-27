#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>

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

  void readMatrixData(std::ifstream &in, int *matrix, std::size_t total)
  {
    for (std::size_t i = 0; i < total; ++i) {
      if (!(in >> matrix[i])) {
        throw std::runtime_error("Not enough elements in matrix or invalid data");
      }
    }
    char c = 0;
    while (in.get(c)) {
      if (!std::isspace(static_cast< unsigned char >(c))) {
        throw std::runtime_error("Invalid data after matrix elements");
      }
    }
  }

  int findRowWithLongestSeries(const int *matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }

    std::size_t best_row = 1;
    std::size_t max_len = 1;

    for (std::size_t i = 0; i < rows; ++i) {
      std::size_t current_len = 1;
      for (std::size_t j = 1; j < cols; ++j) {
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
    return static_cast< int >(best_row);
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

    if (cols != 0
        && static_cast< std::size_t >(rows)
            > std::numeric_limits< std::size_t >::max() / static_cast< std::size_t >(cols)) {
      throw std::runtime_error("Matrix dimensions are too large (overflow)");
    }
    const std::size_t total = static_cast< std::size_t >(rows) * static_cast< std::size_t >(cols);
    int result = 0;

    if (config.mode == 1) {
      const int kMaxSize = 10000;
      if (total > kMaxSize) {
        throw std::runtime_error("Matrix is too large for static array");
      }
      int static_matrix[kMaxSize];
      readMatrixData(in, static_matrix, total);
      result
          = findRowWithLongestSeries(static_matrix, static_cast< std::size_t >(rows), static_cast< std::size_t >(cols));

    } else if (config.mode == 2) {
      int *dynamic_matrix = nullptr;
      try {
        dynamic_matrix = new int[total];
        readMatrixData(in, dynamic_matrix, total);
        result = findRowWithLongestSeries(
            dynamic_matrix, static_cast< std::size_t >(rows), static_cast< std::size_t >(cols));
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
