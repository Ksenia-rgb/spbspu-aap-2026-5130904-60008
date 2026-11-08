#include <iostream>

int main()
{
  int n, m;
  std::cin >> n >> m;

  int** matrix = new int*[n];
  for (int i = 0; i < n; i++)
  {
    matrix[i] = new int[m];
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      std::cin >> matrix[i][j];
    }
  }

  int top = 0, bottom = n - 1;
  int left = 0, right = m - 1;
  int subtract = 1;

  while (top <= bottom && left <= right)
  {
    for (int j = left; j <= right; j++)
    {
      matrix[top][j] -= subtract++;
    }
    top++;

    for (int i = top; i <= bottom; i++)
    {
      matrix[i][right] -= subtract++;
    }
    right--;

    if (top <= bottom)
    {
      for (int j = right; j >= left; j--)
      {
        matrix[bottom][j] -= subtract++;
      }
      bottom--;
    }

    if (left <= right)
    {
      for (int i = bottom; i >= top; i--)
      {
        matrix[i][left] -= subtract++;
      }
      left++;
    }
  }

  std::cout << n << " " << m << "\n";

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (j > 0) std::cout << " ";
      std::cout << matrix[i][j];
    }
    std::cout << "\n";
  }

  for (int i = 0; i < n; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;

  return 0;
}
