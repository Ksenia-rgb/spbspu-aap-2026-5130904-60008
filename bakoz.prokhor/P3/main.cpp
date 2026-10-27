#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <new>

namespace bakoz
{
  const std::string NOT_EGH_ARG = "Not enough arguments";
  const std::string TOO_MANY_ARG = "Too many arguments";
  const std::string FIRST_OUT_RANGE = "First parameter is out of range";
  const std::string FIRST_NOT_NUMBER = "First parameter is not a number";
  const std::string INCOR_FILE_NAME = "Incorrect file name";
  const std::string NOT_MAT_IN_FILE = "No matrix found in the file";
  const std::string CORRUPTED_DATA = "Incorrect format of data";

  constexpr int ARG_EXIT_CODE = 1;
  constexpr int MAT_EXIT_CODE = 2;

  constexpr int BUFFER = 10000;
  constexpr int INT_MAX_LIMIT = INT_MAX;

  struct Matrix
  {
    int line;
    int col;
    int* start;
  };

  void inputdataStatic(std::ifstream& infile, std::ofstream& outfile);
  void inputdataDynamic(std::ifstream& infile, std::ofstream& outfile);
  int countColumnsWithoutNeighbourDuplicates(const Matrix& mat);
}

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << bakoz::NOT_EGH_ARG << "\n";
    return bakoz::ARG_EXIT_CODE;
  }
  if (argc > 4)
  {
    std::cerr << bakoz::TOO_MANY_ARG << "\n";
    return bakoz::ARG_EXIT_CODE;
  }

  const std::string num_param = argv[1];
  int mode = 0;

  if (num_param == "1")
  {
    mode = 1;
  }
  else if (num_param == "2")
  {
    mode = 2;
  }
  else
  {
    bool is_numeric = true;
    for (const char c : num_param)
    {
      if (!std::isdigit(c))
      {
        is_numeric = false;
        break;
      }
    }
    if (is_numeric)
    {
      std::cerr << bakoz::FIRST_OUT_RANGE << "\n";
    }
    else
    {
      std::cerr << bakoz::FIRST_NOT_NUMBER << "\n";
    }
    return bakoz::ARG_EXIT_CODE;
  }

  std::ifstream infile(argv[2]);
  std::ofstream outfile(argv[3]);
  if (!infile.is_open() || !outfile.is_open())
  {
    std::cerr << bakoz::INCOR_FILE_NAME << "\n";
    return bakoz::ARG_EXIT_CODE;
  }

  try
  {
    if (mode == 1)
    {
      bakoz::inputdataStatic(infile, outfile);
    }
    else
    {
      bakoz::inputdataDynamic(infile, outfile);
    }
  }
  catch (const std::invalid_argument& ex)
  {
    std::cerr << ex.what() << "\n";
    return bakoz::MAT_EXIT_CODE;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Allocation failed: Matrix is too big for memory\n";
    return bakoz::MAT_EXIT_CODE;
  }

  return 0;
}

void bakoz::inputdataStatic(std::ifstream& infile, std::ofstream& outfile)
{
  int arr[bakoz::BUFFER] = {0};
  bool has_matrices = false;

  while (true)
  {
    infile >> std::ws;
    if (infile.eof())
    {
      if (!has_matrices)
      {
        throw std::invalid_argument(bakoz::NOT_MAT_IN_FILE);
      }
      break;
    }

    int line = 0;
    infile >> line;

    if (infile.fail())
    {
      throw std::invalid_argument(has_matrices ? bakoz::CORRUPTED_DATA : bakoz::NOT_MAT_IN_FILE);
    }

    int col = 0;
    if (!(infile >> col))
    {
      throw std::invalid_argument(has_matrices ? bakoz::CORRUPTED_DATA : bakoz::NOT_MAT_IN_FILE);
    }

    has_matrices = true;

    if (line < 0 || col < 0)
    {
      throw std::invalid_argument(bakoz::CORRUPTED_DATA);
    }

    if (line == 0 && col == 0)
    {
      outfile << 0 << "\n";
      continue;
    }

    if (col != 0 && line > bakoz::BUFFER / col)
    {
      throw std::invalid_argument(bakoz::CORRUPTED_DATA);
    }

    const int quan_elem = col * line;
    const bakoz::Matrix mat{line, col, arr};

    for (int i = 0; i < quan_elem; ++i)
    {
      if (!(infile >> mat.start[i]))
      {
        throw std::invalid_argument(bakoz::CORRUPTED_DATA);
      }
    }

    const int result = bakoz::countColumnsWithoutNeighbourDuplicates(mat);
    outfile << result << "\n";
  }
}

void bakoz::inputdataDynamic(std::ifstream& infile, std::ofstream& outfile)
{
  bool has_matrices = false;

  while (true)
  {
    infile >> std::ws;
    if (infile.eof())
    {
      if (!has_matrices)
      {
        throw std::invalid_argument(bakoz::NOT_MAT_IN_FILE);
      }
      break;
    }
    int line = 0;
    infile >> line;

    if (infile.fail())
    {
      throw std::invalid_argument(has_matrices ? bakoz::CORRUPTED_DATA : bakoz::NOT_MAT_IN_FILE);
    }

    int col = 0;
    if (!(infile >> col))
    {
      throw std::invalid_argument(has_matrices ? bakoz::CORRUPTED_DATA : bakoz::NOT_MAT_IN_FILE);
    }

    has_matrices = true;

    if (line < 0 || col < 0)
    {
      throw std::invalid_argument(bakoz::CORRUPTED_DATA);
    }

    if (line == 0 && col == 0)
    {
      outfile << 0 << "\n";
      continue;
    }

    if (col != 0 && line > bakoz::INT_MAX_LIMIT / col)
    {
      throw std::invalid_argument(bakoz::CORRUPTED_DATA);
    }

    const int quan_elem = col * line;
    const bakoz::Matrix mat{line, col, new int[quan_elem]{0}};

    for (int i = 0; i < quan_elem; ++i)
    {
      if (!(infile >> mat.start[i]))
      {
        delete[] mat.start;
        throw std::invalid_argument(bakoz::CORRUPTED_DATA);
      }
    }

    const int result = bakoz::countColumnsWithoutNeighbourDuplicates(mat);
    outfile << result << "\n";

    delete[] mat.start;
  }
}

int bakoz::countColumnsWithoutNeighbourDuplicates(const bakoz::Matrix& mat)
{
  if (mat.line <= 0 || mat.col <= 0)
  {
    return 0;
  }

  int valid_columns_count = 0;

  for (int j = 0; j < mat.col; ++j)
  {
    bool has_neighbour_duplicates = false;
    for (int i = 0; i < mat.line - 1; ++i)
    {
      if (mat.start[i * mat.col + j] == mat.start[(i + 1) * mat.col + j])
      {
        has_neighbour_duplicates = true;
        break;
      }
    }
    if (!has_neighbour_duplicates)
    {
      valid_columns_count++;
    }
  }

  return valid_columns_count;
}
