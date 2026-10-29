#include <fstream>
#include <iostream>
#include <new>
#include <string>
#include <limits>

namespace tirkacheva {

  const int MAX_ELEMENTS = 10000;
  const int SUCCESS = 0;
  const int ARGUMENT_ERROR = 1;
  const int INPUT_ERROR = 2;

  int readDimensions(std::ifstream &input, int &rows, int &columns)
  {
    if (!(input >> rows >> columns)) {
      return INPUT_ERROR;
    }

    if (rows < 0 || columns < 0) {
      return INPUT_ERROR;
    }

    if ((rows == 0) != (columns == 0)) {
      return INPUT_ERROR;
    }

    if (columns != 0 && rows > std::numeric_limits< int >::max() / columns) {
      return INPUT_ERROR;
    }

    return SUCCESS;
  }

  int readElements(std::ifstream &input, int matrix[], int rows, int columns)
  {
    const int total = rows * columns;

    for (int i = 0; i < total; i++) {
      if (!(input >> matrix[i])) {
        return INPUT_ERROR;
      }
    }

    return SUCCESS;
  }

  int findBestColumn(const int matrix[], int rows, int columns)
  {
    if (rows == 0 || columns == 0) {
      return 0;
    }

    int max_length = 1;
    int best_column = 1;

    for (int j = 0; j < columns; j++) {
      int current_length = 1;

      for (int i = 1; i < rows; i++) {
        if (matrix[i * columns + j] == matrix[(i - 1) * columns + j]) {
          current_length++;
        } else {
          current_length = 1;
        }

        if (current_length > max_length) {
          max_length = current_length;
          best_column = j + 1;
        }
      }
    }

    return best_column;
  }

  int writeResult(std::ofstream &output, const int result)
  {
    output << result << '\n';

    if (!output) {
      return ARGUMENT_ERROR;
    }

    return SUCCESS;
  }

  int runFixed(std::ifstream &input, std::ofstream &output)
  {
    int matrix[MAX_ELEMENTS];
    int rows = 0;
    int columns = 0;

    input >> std::ws;
    if (input.peek() == std::char_traits< char >::eof()) {
      return INPUT_ERROR;
    }

    int status = readDimensions(input, rows, columns);

    if (status != SUCCESS) {
      return status;
    }

    if (rows * columns > MAX_ELEMENTS) {
      return INPUT_ERROR;
    }

    status = readElements(input, matrix, rows, columns);

    if (status != SUCCESS) {
      return status;
    }

    input >> std::ws;
    if (input.peek() != std::char_traits< char >::eof()) {
      return INPUT_ERROR;
    }

    const int result = findBestColumn(matrix, rows, columns);

    return writeResult(output, result);
  }

  int runDynamic(std::ifstream &input, std::ofstream &output)
  {
    input >> std::ws;
    if (input.peek() == std::char_traits< char >::eof()) {
      return INPUT_ERROR;
    }

    int rows = 0;
    int columns = 0;

    int status = readDimensions(input, rows, columns);

    if (status != SUCCESS) {
      return status;
    }

    const int total = rows * columns;
    int *matrix = nullptr;

    try {
      if (total > 0) {
        matrix = new int[total];
      }
    } catch (const std::bad_alloc &) {
      std::cerr << "Memory allocation error\n";
      return INPUT_ERROR;
    }

    status = readElements(input, matrix, rows, columns);

    if (status != SUCCESS) {
      delete[] matrix;
      return status;
    }

    input >> std::ws;
    if (input.peek() != std::char_traits< char >::eof()) {
      delete[] matrix;
      return INPUT_ERROR;
    }

    const int result = findBestColumn(matrix, rows, columns);
    delete[] matrix;

    return writeResult(output, result);
  }
}

int main(int argc, char *argv[])
{
  using namespace tirkacheva;

  if (argc != 4) {
    std::cerr << "Invalid number of arguments\n";
    return ARGUMENT_ERROR;
  }

  const std::string variant = argv[1];

  if (variant != "1" && variant != "2") {
    std::cerr << "Invalid variant\n";
    return ARGUMENT_ERROR;
  }

  std::ifstream input(argv[2]);

  if (!input) {
    std::cerr << "Cannot open input file\n";
    return INPUT_ERROR;
  }

  std::ofstream output(argv[3]);

  if (!output) {
    std::cerr << "Cannot open output file\n";
    return ARGUMENT_ERROR;
  }

  int status = SUCCESS;

  if (variant == "1") {
    status = runFixed(input, output);
  } else {
    status = runDynamic(input, output);
  }

  if (status == INPUT_ERROR) {
    std::cerr << "Invalid input data\n";
  }

  return status;
}
