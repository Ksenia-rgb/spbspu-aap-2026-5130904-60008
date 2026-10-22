#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

namespace stremetskiy
{
  void readRowAndCol(std::string, int *, int *);
  void fillArr(std::string, int *, int, int);
  int **fillArr(std::string, int, int);
  void writeResult(std::string, int);
  constexpr int INVALID_INPUT = 1;
  constexpr int INVALID_FILE = 2;
  constexpr int SIZE_FIX = 100;
}

int main(int argc, char *argv[])
{
  int count = 0;
  int variant = 0;

  std::string input = "";
  std::string output = "";

  int row = 0;
  int col = 0;

  try
  {
    if (argc < 4)
    {
      throw std::range_error("Not enough arguments\n");
    }

    if (argc > 4)
    {
      throw std::range_error("too many arguments\n");
    }

    variant = std::stoi(argv[1]);
    input = argv[2];
    output = argv[3];

    stremetskiy::readRowAndCol(input, &row, &col);
    if (variant == 1)
    {
      int array[stremetskiy::SIZE_FIX][stremetskiy::SIZE_FIX] = {0};
      stremetskiy::fillArr(input, array[0], row, col);

      for (int i = 1; i < (row - 1); i++)
      {
        for (int j = 1; j < (col - 1); j++)
        {
          const int a = array[i][j];
          if (a > array[i - 1][j] && a > array[i + 1][j])
          {
            if (a > array[i][j - 1] && a > array[i][j + 1])
            {
              count++;
            }
          }
        }
      }
    }
    else if (variant == 2)
    {
      int *const *const array = stremetskiy::fillArr(input, row, col);

      for (int i = 1; i < (row - 1); i++)
      {
        for (int j = 1; j < (col - 1); j++)
        {
          const int a = array[i][j];
          if (a > array[i - 1][j] && a > array[i + 1][j])
          {
            if (a > array[i][j - 1] && a > array[i][j + 1])
            {
              count++;
            }
          }
        }
      }

      for (int i = 0; i < row; i++)
      {
        delete[] array[i];
      }
      delete[] array;
    }
    else
    {
      throw std::range_error("First value is out of range\n");
    }
  }
  catch (const std::range_error &ex)
  {
    std::cerr << "Invalid input: " << ex.what();
    return stremetskiy::INVALID_INPUT;
  }
  catch (const std::invalid_argument &ex)
  {
    std::cerr << "Invalid input: First value is not a num \n";
    return stremetskiy::INVALID_INPUT;
  }
  catch (const std::logic_error &ex)
  {
    std::cerr << "Input file problem: " << ex.what();
    return stremetskiy::INVALID_FILE;
  }

  stremetskiy::writeResult(output, count);

  return 0;
}

namespace stremetskiy
{
  void readRowAndCol(std::string file, int *row, int *col)
  {
    std::ifstream in(file);

    int val = 0;

    if (in.is_open())
    {
      if (!(in >> val))
      {
        throw std::logic_error("Invalid file content\n");
      }
      *row = val;
      if (!(in >> val))
      {
        throw std::logic_error("Invalid file content\n");
      }
      *col = val;
    }
    else
    {
      throw std::logic_error("input file cannot be opened\n");
    }
  }

  void fillArr(std::string file, int arr[], int row, int col)
  {
    std::ifstream in(file);

    int val = 0;

    if (in.is_open())
    {
      in >> val;
      in >> val;

      for (int i = 0; i < row; i++)
      {
        for (int j = 0; j < col; j++)
        {
          if (!(in >> val))
          {
            throw std::logic_error("Invalid file content\n");
          }
          *(arr + i * stremetskiy::SIZE_FIX + j) = val;
        }
      }
    }
    else
    {
      throw std::logic_error("input file cannot be opened\n");
    }
  }

  int **fillArr(std::string file, int row, int col)
  {
    std::ifstream in(file);

    int val = 0;

    if (in.is_open())
    {
      in >> val;
      in >> val;

      int **const result_arr = new int *[row];
      for (int i = 0; i < row; i++)
      {
        result_arr[i] = new int[col];
      }

      for (int i = 0; i < row; i++)
      {
        for (int j = 0; j < col; j++)
        {
          if (!(in >> val))
          {
            for (int k = 0; k <= i; k++)
            {
              delete[] result_arr[k];
            }
            delete[] result_arr;
            throw std::logic_error("Invalid file content\n");
          }
          result_arr[i][j] = val;
        }
      }
      return result_arr;
    }
    else
    {
      throw std::logic_error("input file cannot be opened\n");
    }
  }

  void writeResult(std::string file, int result)
  {
    std::ofstream out(file);

    if (out.is_open())
    {
      out << result;
    }
    else
    {
      throw std::logic_error("output file cannot be opened\n");
    }
  }
}
