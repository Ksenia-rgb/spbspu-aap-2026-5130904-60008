#include <iostream>
#include <fstream>

namespace kilyan
{
  const int MAX_STATIC_ELEMENTS = 10000;
  const int SUCCESS = 0;
  const int ARGUMENT_ERROR = 1;
  const int INPUT_ERROR = 2;
  int readDimensions(std::ifstream& infile, int& rows, int& cols)
  {
    if (!(infile >> rows >> cols))
    {
      return INPUT_ERROR;
    }
    if (rows < 0 || cols < 0)
    {
      return INPUT_ERROR;
    }
    if ((rows == 0 && cols != 0) || (cols == 0 && rows != 0))
    {
      return INPUT_ERROR;
    }
    if (cols > 0)
    {
      const int max_int = 2147483647;
      if (rows > max_int / cols)
      {
        return INPUT_ERROR;
      }
    }
    return SUCCESS;
  }
  int readElements(std::ifstream& infile, int* matrix_ptr, int rows, int cols)
  {
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(infile >> matrix_ptr[i * cols + j]))
        {
          return INPUT_ERROR;
        }
      }
    }
    return SUCCESS;
  }
  int countSaddlePoints(const int* matrix_ptr, int rows, int cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    int saddle_count = 0;
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        const int current = matrix_ptr[i * cols + j];
        bool is_min_in_row = true;
        for (int k = 0; k < cols; ++k)
        {
          if (current > matrix_ptr[i * cols + k])
          {
            is_min_in_row = false;
            break;
          }
        }
        bool is_max_in_col = true;
        if (is_min_in_row)
        {
          for (int k = 0; k < rows; k++)
          {
            if (current < matrix_ptr[k * cols + j])
            {
              is_max_in_col = false;
              break;
            }
          }
        }
        if (is_min_in_row && is_max_in_col)
        {
          saddle_count++;
        }
      }
    }
    return saddle_count;
  }
  int writeResult(std::ofstream& outfile, int result)
  {
    outfile << result << "\n";
    if (!outfile)
    {
      std::cerr << "Error: Failed to write the result to the output file\n";
      return ARGUMENT_ERROR;
    }
    return SUCCESS;
  }
  int runFixed(std::ifstream& infile, std::ofstream& outfile)
  {
    infile >> std::ws;
    if (infile.peek() == EOF)
    {
      return INPUT_ERROR;
    }
    int rows = 0, cols = 0;
    int status = readDimensions(infile, rows, cols);
    if (status != SUCCESS)
    {
      return status;
    }
    if (rows * cols > MAX_STATIC_ELEMENTS)
    {
      return INPUT_ERROR;
    }
    int static_matrix[MAX_STATIC_ELEMENTS];
    status = readElements(infile, static_matrix, rows, cols);
    if (status != SUCCESS)
    {
      return status;
    }
    infile >> std::ws;
    if (infile.peek() != EOF)
    {
      return INPUT_ERROR;
    }
    const int result = countSaddlePoints(static_matrix, rows, cols);
    return writeResult(outfile, result);
  }
  int runDynamic(std::ifstream& infile, std::ofstream& outfile)
  {
    infile >> std::ws;
    if (infile.peek() == EOF)
    {
      return INPUT_ERROR;
    }
    int rows = 0, cols = 0;
    int status = readDimensions(infile, rows, cols);
    if (status != SUCCESS)
    {
      return status;
    }
    const int total = rows * cols;
    if (total == 0)
    {
      infile >> std::ws;
      if (infile.peek() != EOF)
      {
        return INPUT_ERROR;
      }
      return writeResult(outfile, 0);
    }
    int* const dynamic_matrix = new int[total];
    status = readElements(infile, dynamic_matrix, rows, cols);
    if (status != SUCCESS)
    {
      delete[] dynamic_matrix;
      return status;
    }
    infile >> std::ws;
    if (infile.peek() != EOF)
    {
      delete[] dynamic_matrix;
      return INPUT_ERROR;
    }
    const int result = countSaddlePoints(dynamic_matrix, rows, cols);
    const int write_status = writeResult(outfile, result);
    delete[] dynamic_matrix;
    return write_status;
  }
}
int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Invalid command line arguments\n";
    return kilyan::ARGUMENT_ERROR;
  }
  else
  {
    const char* const mode_str = argv[1];
    if (mode_str[0] == '\0' || mode_str[1] != '\0' || (mode_str[0] != '1' && mode_str[0] != '2'))
    {
      std::cerr << "Error: Invalid mode\n";
      return kilyan::ARGUMENT_ERROR;
    }
    const char mode = mode_str[0];
    std::ifstream input(argv[2]);
    if (!input)
    {
      std::cerr << "Error: Failed to open input file\n";
      return kilyan::INPUT_ERROR;
    }
    std::ofstream output(argv[3]);
    if (!output)
    {
      std::cerr << "Error: Failed to open output file\n";
      return kilyan::ARGUMENT_ERROR;
    }
    int status = kilyan::SUCCESS;
    if (mode == '1')
    {
      status = kilyan::runFixed(input, output);
    }
    else
    {
      status = kilyan::runDynamic(input, output);
    }
    if (status == kilyan::INPUT_ERROR)
    {
      std::cerr << "Error: Invalid input data\n";
    }
    return status;
  }
}
