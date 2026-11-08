#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: main <type> <in> <out>\n";
    return 1;
  }

  if (argv[1][0] != '1' && argv[1][0] != '2')
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
  if (!(in >> n >> m) || n < 0 || m < 0)
  {
    std::cerr << "Bad size\n";
    return 1;
  }

  int* const* const matrix = new int*[n];
  for (int i = 0; i < n; ++i)
  {
    matrix[i] = new int[m];
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (!(in >> matrix[i][j]))
      {
        for (int k = 0; k < n; ++k)
        {
          delete[] matrix[k];
        }
        delete[] matrix;
        std::cerr << "Bad data\n";
        return 1;
      }
    }
  }

  int top = 0;
  int bottom = n - 1;
  int left = 0;
  int right = m - 1;
  int sub = 1;

  while (top <= bottom && left <= right)
  {
    for (int j = left; j <= right; ++j)
    {
      matrix[top][j] -= sub++;
    }
    ++top;

    for (int i = top; i <= bottom; ++i)
    {
      matrix[i][right] -= sub++;
    }
    --right;

    if (top <= bottom)
    {
      for (int j = right; j >= left; --j)
      {
        matrix[bottom][j] -= sub++;
      }
      --bottom;
    }

    if (left <= right)
    {
      for (int i = bottom; i >= top; --i)
      {
        matrix[i][left] -= sub++;
      }
      ++left;
    }
  }

  out << n << " " << m << "\n";
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (j > 0)
      {
        out << " ";
      }
      out << matrix[i][j];
    }
    out << "\n";
  }

  for (int i = 0; i < n; ++i)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
  return 0;
}
