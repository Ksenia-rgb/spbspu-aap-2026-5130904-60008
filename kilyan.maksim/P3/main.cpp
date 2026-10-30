#include <iostream>
#include <fstream>

namespace kilyan
{
  const int MAX_STATIC_ELEMENTS = 10000;
  const int SUCCESS = 0;
  const int ARGUMENT_ERROR = 1;
  const int INPUT_ERROR = 2;
  int ReadDimensions(std::ifstream& infile, int& rows, int& cols)
  {
    if (!(infile >> rows >> cols) || rows <= 0 || cols <= 0)
    {
      std::cerr << "Error: Invalid matrix dimensions or failed to read rows/cols\n";
      return INPUT_ERROR;
    }
    return SUCCESS;
  }
  int ReadElements(std::ifstream& infile, int* matrix_ptr, int rows, int cols)
  {
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(infile >> matrix_ptr[i * cols + j]))
        {
          std::cerr << "Error: Failed to read matrix element\n";
          return INPUT_ERROR;
        }
      }
    }
    return SUCCESS;
  }
  int CountSaddlePoints(const int* matrix_ptr, int rows, int cols)
  {
    int saddle_count = 0;
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        int current = matrix_ptr[i * cols + j];
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
  int WriteResult(std::ofstream& outfile, int result)
  {
    outfile << result << "\n";
    if (!outfile)
    {
      std::cerr << "Error: Failed to write the result to the output file\n";
      return ARGUMENT_ERROR;
    }
    return SUCCESS;
  }
  int RunFixed(std::ifstream& infile, std::ofstream& outfile)
  {
    int rows = 0, cols = 0;
    int status = ReadDimensions(infile, rows, cols);
    if (status != 0) return status;
    int static_matrix[10000];
    if (rows * cols > 10000)
    {
      std::cerr << "Error: Matrix size exceeds static limit of " << MAX_STATIC_ELEMENTS << "\n";
      return INPUT_ERROR;
    }
    status = ReadElements(infile, static_matrix, rows, cols);
    if (status != 0) return status;
    int result = CountSaddlePoints(static_matrix, rows, cols);
    return WriteResult(outfile, result);
  }
  int RunDynamic(std::ifstream& infile, std::ofstream& outfile)
  {
    int rows = 0, cols = 0;
    int status = ReadDimensions(infile, rows, cols);
    if (status != 0) return status;
    int* dynamic_matrix = new int[rows * cols];
    status = ReadElements(infile, dynamic_matrix, rows, cols);
    if (status != 0)
    {
      delete[] dynamic_matrix;
      return status;
    }
    int extra_element;
    if (infile >> extra_element)
    {
      std::cerr << "Error: Redundant elements found at the end of the file\n";
      delete[] dynamic_matrix;
      return INPUT_ERROR;
    }
    int result = CountSaddlePoints(dynamic_matrix, rows, cols);
    int write_status = WriteResult(outfile, result);
    delete[] dynamic_matrix;
    return write_status;
  }
}
int main(int argc, char* argv[])
{
  if (argc != 4 || *argv[1] == '\0' || *(argv[1] + 1) != '\0')
  {
    std::cerr << "Error: Invalid command line arguments\n";
    return kilyan::ARGUMENT_ERROR;
  }
  char mode = *argv[1];
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
  int status = 0;
  switch(mode)
  {
  case '1':
      status = kilyan::RunFixed(input, output);
      break;
  case '2':
      status = kilyan::RunDynamic(input, output);
      break;
  default:
      std::cerr << "Error: Invalid mode\n";
      return kilyan::INPUT_ERROR;
  }
  return status;
}
