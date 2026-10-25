#include <fstream>
#include <iostream>
#include <string>

namespace koshutin
{
  const std::string LESS_ARG = "Not enough arguments";
  const std::string MUCH_ARG = "Too many arguments";
  const std::string NOT_A_NUMBER = "Argument is not a number";
  const std::string OUT_OF_RANGE = "Argument is out of range";
  const std::string INV_DATA = "Invalid array";
  const int MAX_LENGTH = 10000;

  int ReadElements(std::ifstream &input, int *massive, int rows, int cols);
  long CountRowsWithoutEqualNumbers(const int *massive, int rows, int cols);
}

int main(int argc, char *argv[])
{

  if (argc < 4)
  {
    std::cerr << koshutin::LESS_ARG << "\n";
    return 1;
  }

  else if (argc > 4)
  {
    std::cerr << koshutin::MUCH_ARG << "\n";
    return 1;
  }

  const std::string num = argv[1];

  if (num != "2" && num != "1")
  {
    std::cerr << koshutin::NOT_A_NUMBER << "\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  int rows = 0, cols = 0;

  if (!input)
  {
    std::cerr << "Invalid file" << "\n";
    return 2;
  }

  if (!(input >> rows >> cols))
  {
    std::cerr << koshutin::INV_DATA << "\n";
    return 2;
  }

  if (rows < 0 || cols < 0)
  {
    std::cerr << koshutin::INV_DATA << "\n";
    return 2;
  }

  long n = static_cast<long>(rows) * cols;
  long answer = 0;

  if (num == "1")
  {
    if (n > koshutin::MAX_LENGTH)
    {
      std::cerr << koshutin::INV_DATA << "\n";
      return 2;
    }
    int massive[koshutin::MAX_LENGTH];
    if (koshutin::ReadElements(input, massive, rows, cols) != 0)
    {
      return 2;
    }
    answer = koshutin::CountRowsWithoutEqualNumbers(massive, rows, cols);
  }

  if (num == "2") {
    int *massive = nullptr;
    try
    {
      massive = new int[n];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << koshutin::INV_DATA << "\n";
    }
    if (koshutin::ReadElements(input, massive, rows, cols) != 0)
    {
      delete[] massive;
      return 2;
    }
    answer = koshutin::CountRowsWithoutEqualNumbers(massive, rows, cols);
    delete[] massive;
  }

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Invalid file" << "\n";
    return 2;
  }
  output << answer << "\n";
  return 0;
}

namespace koshutin
{
  int ReadElements(std::ifstream &input, int *massive, int rows, int cols) {
    long n = static_cast<long>(rows) * cols;
    for (long i = 0; i < n; ++i)
    {
      if (!(input >> massive[i])) {
      std::cerr << koshutin::INV_DATA << "\n";
      return 2;
      }
    }
    return 0;
  }

  long CountRowsWithoutEqualNumbers(const int *massive, int rows, int cols) {
    long count = 0;
    for (int i = 0; i < rows; ++i) {
      bool norm = true;
      for (int j = 0; j + 1 < cols; ++j) {
        if (massive[i * cols + j] == massive[i * cols + j + 1])
        {
          norm = false;
          break;
        }
      }
      if (norm)
      {
        ++count;
      }
    }
    return count;
  }

}
