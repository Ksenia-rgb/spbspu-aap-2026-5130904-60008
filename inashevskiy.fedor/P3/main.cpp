#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>

namespace inashevskiy
{
  const std::string NOT_EN_ARG = "not enough arguments";
  const std::string TOO_MANY_ARG = "too many arguments";
  const std::string FIRST_OUT_RANGE = "First parameter is out of range";
  const std::string FIRST_NOT_NUMBER = "First parameter is not a number";
  const std::string INCOR_FILE_NAME = "Incorrect file name";
  const std::string NOT_MAT_IN_FILE = "No matrix found in the file";
  const int ARG_EXIT_CODE = 1;
  const int MAT_EXIT_CODE = 2;
  const int MAX_FIXED_SIZE = 10000;
}

bool isInteger(const char* s)
{
  int i = 0;
  if (s[0] == '+' || s[0] == '-')
  {
    i++;
  }
  if (s[i] == '\0')
  {
    return false;
  }
  for (; s[i] != '\0'; i++)
  {
    if (!std::isdigit(static_cast< unsigned char >(s[i])))
    {
      return false;
    }
  }
  return true;
}

bool readHeader(std::ifstream& in, int& rows, int& cols)
{
  if (!(in >> rows >> cols))
  {
    return false;
  }
  if (rows < 0 || cols < 0)
  {
    return false;
  }
  return true;
}

bool readElements(std::ifstream& in, int* a, long long count)
{
  for (long long i = 0; i < count; i++)
  {
    if (!(in >> a[i]))
    {
      return false;
    }
  }
  int extra = 0;
  if (in >> extra)
  {
    return false;
  }
  in.clear();
  in >> std::ws;
  if (!in.eof())
  {
    return false;
  }
  return true;
}

void process(int* a, int r, int c)
{
  int top = 0;
  int bottom = r - 1;
  int left = 0;
  int right = c - 1;
  int k = 1;
  while (top <= bottom && left <= right)
  {
    for (int i = bottom; i >= top; i--)
    {
      a[i * c + left] -= k++;
    }
    left++;
    if (left > right)
    {
      break;
    }

    for (int j = left; j <= right; j++)
    {
      a[top * c + j] -= k++;
    }
    top++;
    if (top > bottom)
    {
      break;
    }

    for (int i = top; i <= bottom; i++)
    {
      a[i * c + right] -= k++;
    }
    right--;
    if (left > right)
    {
      break;
    }

    for (int j = right; j >= left; j--)
    {
      a[bottom * c + j] -= k++;
    }
    bottom--;
  }
}

bool writeResult(const char* name, const int* a, int r, int c)
{
  std::ofstream out(name);
  if (!out)
  {
    return false;
  }
  out << r << ' ' << c;
  for (long long i = 0; i < static_cast< long long >(r) * c; i++)
  {
    out << ' ' << a[i];
  }
  out << '\n';
  return static_cast< bool >(out);
}

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << inashevskiy::NOT_EN_ARG;
    return inashevskiy::ARG_EXIT_CODE;
  }
  if (argc > 4)
  {
    std::cerr << inashevskiy::TOO_MANY_ARG;
    return inashevskiy::ARG_EXIT_CODE;
  }

  if (!isInteger(argv[1]))
  {
    std::cerr << inashevskiy::FIRST_NOT_NUMBER;
    return inashevskiy::ARG_EXIT_CODE;
  }
  int num = 0;
  if (std::strcmp(argv[1], "1") == 0)
  {
    num = 1;
  }
  else if (std::strcmp(argv[1], "2") == 0)
  {
    num = 2;
  }
  else
  {
    std::cerr << inashevskiy::FIRST_OUT_RANGE;
    return inashevskiy::ARG_EXIT_CODE;
  }

  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << inashevskiy::INCOR_FILE_NAME;
    return inashevskiy::MAT_EXIT_CODE;
  }

  int rows = 0;
  int cols = 0;

  if (!readHeader(in, rows, cols))
  {
    std::cerr << inashevskiy::NOT_MAT_IN_FILE;
    return inashevskiy::MAT_EXIT_CODE;
  }
  const long long count = static_cast< long long >(rows) * cols;

  if (num == 1)
  {
    int fixed_arr[inashevskiy::MAX_FIXED_SIZE];

    if (count > inashevskiy::MAX_FIXED_SIZE)
    {
      std::cerr << inashevskiy::NOT_MAT_IN_FILE;
      return inashevskiy::MAT_EXIT_CODE;
    }
    if (!readElements(in, fixed_arr, count))
    {
      std::cerr << inashevskiy::NOT_MAT_IN_FILE;
      return inashevskiy::MAT_EXIT_CODE;
    }
    process(fixed_arr, rows, cols);
    if (!writeResult(argv[3], fixed_arr, rows, cols))
    {
      std::cerr << inashevskiy::INCOR_FILE_NAME;
      return inashevskiy::ARG_EXIT_CODE;
    }
  }
  else
  {
    int* const dyn = new int[count > 0 ? count : 1];
    if (!readElements(in, dyn, count))
    {
      std::cerr << inashevskiy::NOT_MAT_IN_FILE;
      delete[] dyn;
      return inashevskiy::MAT_EXIT_CODE;
    }
    process(dyn, rows, cols);
    const bool ok = writeResult(argv[3], dyn, rows, cols);
    delete[] dyn;
    if (!ok)
    {
      std::cerr << inashevskiy::INCOR_FILE_NAME;
      return inashevskiy::ARG_EXIT_CODE;
    }
  }
  return 0;
}
