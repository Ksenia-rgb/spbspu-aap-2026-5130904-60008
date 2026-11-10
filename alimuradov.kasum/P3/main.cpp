#include <cctype>
#include <fstream>
#include <iostream>

namespace alimuradov
{

constexpr int kMaxSize = 100;

}

using alimuradov::kMaxSize;

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: main <1|2> <in> <out>\n";
    return 1;
  }

  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "Bad type\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);
  if (!in || !out)
  {
    std::cerr << "File error\n";
    return 1;
  }

  int n = 0;
  int m = 0;
  if (!(in >> n >> m) || n < 0 || m < 0 || n > kMaxSize || m > kMaxSize)
  {
    std::cerr << "Bad size\n";
    return 2;
  }

  int** matrix = nullptr;
  int fixed[kMaxSize][kMaxSize] = {};
  const bool dynamic = (argv[1][0] == '2');

  if (dynamic)
  {
    matrix = new int*[n];
    for (int i = 0; i < n; ++i)
    {
      matrix[i] = new int[m];
    }
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      int* const cell = dynamic ? &matrix[i][j] : &fixed[i][j];
      if (!(in >> *cell))
      {
        std::cerr << "Bad data\n";
        if (dynamic)
        {
          for (int k = 0; k < n; ++k)
          {
            delete[] matrix[k];
          }
          delete[] matrix;
        }
        return 2;
      }
      char c = 0;
      if (in.get(c) && !std::isspace(static_cast<unsigned char>(c)))
      {
        std::cerr << "Bad data\n";
        if (dynamic)
        {
          for (int k = 0; k < n; ++k)
          {
            delete[] matrix[k];
          }
          delete[] matrix;
        }
        return 2;
      }
    }
  }

  int extra = 0;
  if (in >> extra)
  {
    std::cerr << "Trailing data\n";
    if (dynamic)
    {
      for (int k = 0; k < n; ++k)
      {
        delete[] matrix[k];
      }
      delete[] matrix;
    }
    return 2;
  }

  int top = 0;
  int bottom = n - 1;
  int left = 0;
  int right = m - 1;
  long long sub = 1;

  while (top <= bottom && left <= right)
  {
    for (int j = left; j <= right; ++j)
    {
      int* const cell = dynamic ? &matrix[top][j] : &fixed[top][j];
      *cell = static_cast<int>(*cell - sub++);
    }
    ++top;

    for (int i = top; i <= bottom; ++i)
    {
      int* const cell = dynamic ? &matrix[i][right] : &fixed[i][right];
      *cell = static_cast<int>(*cell - sub++);
    }
    --right;

    if (top <= bottom)
    {
      for (int j = right; j >= left; --j)
      {
        int* const cell = dynamic ? &matrix[bottom][j] : &fixed[bottom][j];
        *cell = static_cast<int>(*cell - sub++);
      }
      --bottom;
    }

    if (left <= right)
    {
      for (int i = bottom; i >= top; --i)
      {
        int* const cell = dynamic ? &matrix[i][left] : &fixed[i][left];
        *cell = static_cast<int>(*cell - sub++);
      }
      ++left;
    }
  }

  out << n << " " << m << "\n";
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      const int value = dynamic ? matrix[i][j] : fixed[i][j];
      if (j > 0)
      {
        out << " ";
      }
      out << value;
    }
    out << "\n";
  }

  if (dynamic)
  {
    for (int i = 0; i < n; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  out.flush();
  if (!out)
  {
    std::cerr << "Write error\n";
    return 1;
  }
  return 0;
}
