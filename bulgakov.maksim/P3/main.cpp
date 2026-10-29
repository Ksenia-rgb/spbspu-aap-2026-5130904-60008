#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <limits>

namespace bulgakov
{
  const std::string ERR_ARGS = "Invalid number of arguments!\n";
  const std::string ERR_PARAM = "First parameter must be 1 or 2!\n";
  const std::string ERR_OPEN_IN = "Cannot open input file!\n";
  const std::string ERR_DIMENSIONS = "Invalid matrix dimensions in file!\n";
  const std::string ERR_STACK_LIMIT = "Matrix size exceeds 10000 elements for stack allocation!\n";
  const std::string ERR_CORRUPT_DATA = "Invalid matrix elements or unexpected end of file!\n";
  const std::string ERR_OPEN_OUT = "Cannot open output file!\n";

  constexpr int MAX_STACK_SIZE = 10000;

  void processMatrix(int* a, int rows, int cols);
  void processMatrix(int** a, int rows, int cols);
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << bulgakov::ERR_ARGS;
    return 1;
  }

  const std::string num_str = argv[1];
  if (num_str != "1" && num_str != "2")
  {
    std::cerr << bulgakov::ERR_PARAM;
    return 1;
  }
  const int num = std::stoi(num_str);

  const std::string input_filename = argv[2];
  const std::string output_filename = argv[3];

  std::ifstream fin(input_filename);
  if (!fin.is_open())
  {
    std::cerr << bulgakov::ERR_OPEN_IN;
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(fin >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << bulgakov::ERR_DIMENSIONS;
    return 2;
  }

  std::ofstream fout(output_filename);
  if (!fout.is_open())
  {
    std::cerr << bulgakov::ERR_OPEN_OUT;
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    fout << 0 << " " << 0 << "\n";
    return 0;
  }

  int* matrix = nullptr;
  int stack_matrix[bulgakov::MAX_STACK_SIZE];

  if (rows <= 0 || cols <= 0)
  {
    std::cerr << bulgakov::ERR_CORRUPT_DATA;
    return 2;
  }

  if (rows > std::numeric_limits<int>::max() / cols)
  {
    std::cerr << bulgakov::ERR_CORRUPT_DATA;
    return 2;
  }
  

  if (num == 1)
  {
    if (rows * cols > bulgakov::MAX_STACK_SIZE)
    {
      std::cerr << bulgakov::ERR_STACK_LIMIT;
      return 2;
    }
    matrix = stack_matrix;
  }
  else
  {
    try
    {
      matrix = new int[rows * cols];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << bulgakov::ERR_CORRUPT_DATA;
      return 2;
    }
  }

  for (int i = 0; i < rows * cols; ++i)
  {
    if (!(fin >> matrix[i]))
    {
      std::cerr << bulgakov::ERR_CORRUPT_DATA;
      if (num == 2)
      {
        delete[] matrix;
      }
      return 2;
    }
  }

  char trailing_char = '0';
  if (fin >> trailing_char)
  {
    std::cerr << bulgakov::ERR_CORRUPT_DATA;
    if (num == 2)
    {
      delete[] matrix;
    }
    return 2;
  }
  fin.close();

  bulgakov::processMatrix(matrix, rows, cols);

  fout << rows << " " << cols << "\n";
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      fout << matrix[i * cols + j] << (j == cols - 1 ? "" : " ");
    }
    fout << "\n";
  }
  fout.close();

  if (num == 2)
  {
    delete[] matrix;
  }

  return 0;
}

void bulgakov::processMatrix(int* a, int rows, int cols)
{
  if (rows <= 0 || cols <= 0 || a == nullptr)
  {
    return;
  }

  const int total_elements = rows * cols;
  int increment = 1;

  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;

  while (increment <= total_elements)
  {
    for (int r = top; r <= bottom && increment <= total_elements; ++r)
    {
      a[r * cols + left] += increment;
      increment++;
    }
    left++;

    for (int c = left; c <= right && increment <= total_elements; ++c)
    {
      a[bottom * cols + c] += increment;
      increment++;
    }
    bottom--;

    for (int r = bottom; r >= top && increment <= total_elements; --r)
    {
      a[r * cols + right] += increment;
      increment++;
    }
    right--;

    for (int c = right; c >= left && increment <= total_elements; --c)
    {
      a[top * cols + c] += increment;
      increment++;
    }
    top++;
  }
}

void bulgakov::processMatrix(int** a, int rows, int cols)
{
  if (rows <= 0 || cols <= 0 || a == nullptr)
  {
    return;
  }

  int* const flat = new int[rows * cols];

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      flat[i * cols + j] = a[i][j];
    }
  }

  processMatrix(flat, rows, cols);

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      a[i][j] = flat[i * cols + j];
    }
  }

  delete[] flat;
}
