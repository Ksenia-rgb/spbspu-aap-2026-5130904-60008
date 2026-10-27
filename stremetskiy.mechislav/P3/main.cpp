#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <cstddef>
#include <cstdio>

namespace stremetskiy
{
  void readRowAndCol(std::string, int *, int *);
  void fillArr(std::string, int *, int, int);
  int **fillArr(std::string, int, int);
  void writeResult(std::string, int);
  constexpr int INVALID_INPUT = 1;
  constexpr int INVALID_FILE = 2;
  constexpr int MAXSIZE_FIX = 10000;
}

int main(int argc, char *argv[])
{
  int count = 0;
  int variant = 0;

  size_t parsed_chars = 0;

  std::string variant_str = "";
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

    variant_str = argv[1];

    variant = std::stoi(argv[1], &parsed_chars);

    if (parsed_chars != variant_str.length())
    {
      throw std::runtime_error("First value is not a num\n");
    }

    input = argv[2];
    output = argv[3];

    stremetskiy::readRowAndCol(input, &row, &col);
    if (variant == 1)
    {
      int array[stremetskiy::MAXSIZE_FIX] = {0};
      stremetskiy::fillArr(input, array, row, col);

      for (int i = 1; i < (row - 1); i++)
      {
        for (int j = 1; j < (col - 1); j++)
        {
          const int a1 = array[((i - 1) * col) + j - 1];
          const int a2 = array[((i - 1) * col) + j];
          const int a3 = array[((i - 1) * col) + j + 1];
          const int a4 = array[(i * col) + j - 1];
          const int a = array[(i * col) + j];
          const int a6 = array[(i * col) + j + 1];
          const int a7 = array[((i + 1) * col) + j - 1];
          const int a8 = array[((i + 1) * col) + j];
          const int a9 = array[((i + 1) * col) + j + 1];

          if (a > a1 && a > a2 && a > a3 && a > a4 && a > a6 && a > a7)
          {
            if (a > a8 && a > a9)
            {
              count++;
            }
          }
        }
      }
      stremetskiy::writeResult(output, count);
    }
    else if (variant == 2)
    {
      int **const array = stremetskiy::fillArr(input, row, col);

      for (int i = 1; i < (row - 1); i++)
      {
        for (int j = 1; j < (col - 1); j++)
        {
          const int a = array[i][j];
          if (a > array[i - 1][j] && a > array[i + 1][j])
          {
            if (a > array[i][j - 1] && a > array[i][j + 1])
            {
              if (a > array[i - 1][j - 1] && a > array[i + 1][j + 1])
              {
                if (a > array[i - 1][j + 1] && a > array[i + 1][j - 1])
                {
                  count++;
                }
              }
            }
          }
        }
      }

      stremetskiy::writeResult(output, count);

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
  catch (const std::out_of_range &)
  {
    std::cerr << "Invalid input: First out of range \n";
    return stremetskiy::INVALID_INPUT;
  }
  catch (const std::logic_error &ex)
  {
    std::cerr << "Input file problem: " << ex.what();
    return stremetskiy::INVALID_FILE;
  }
  catch (const std::runtime_error &ex)
  {
    std::cerr << "Invalid input: " << ex.what();
    return stremetskiy::INVALID_INPUT;
  }
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
      if (!(in >> val) || val < 0)
      {
        throw std::logic_error("Invalid file content\n");
      }
      *row = val;
      if (!(in >> val) || val < 0)
      {
        throw std::logic_error("Invalid file content\n");
      }
      *col = val;
    }
    else
    {
      throw std::runtime_error("input file cannot be opened\n");
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
          *(arr + (i * col) + j) = val;
        }
      }

      in >> std::ws;
      if (in.get() != EOF)
      {
        throw std::logic_error("extra data at the end of file\n");
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

      in >> std::ws;
      if (in.get() != EOF)
      {
        for (int k = 0; k < row; k++)
        {
          delete[] result_arr[k];
        }
        delete[] result_arr;
        throw std::logic_error("extra data at the end of file\n");
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
      throw std::runtime_error("output file cannot be opened\n");
    }
  }
}
