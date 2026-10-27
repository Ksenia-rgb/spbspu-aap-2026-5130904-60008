#include <cstring>
#include <fstream>
#include <iostream>

namespace kiriukhin {

  const int kMaxStaticSize = 10000;

  enum ExitCode { kOk = 0, kBadArgs = 1, kBadInput = 2 };

  bool readDimensions(std::ifstream &in, int &rows, int &cols)
  {
    if (!(in >> rows >> cols)) {
      return false;
    }
    return rows >= 0 && cols >= 0;
  }

  bool readElements(std::ifstream &in, int *data, long long count)
  {
    for (long long i = 0; i < count; ++i) {
      if (!(in >> data[i])) {
        return false;
      }
    }
    in >> std::ws;
    return in.eof();
  }

  int countLocalMax(const int *a, int rows, int cols)
  {
    int result = 0;
    for (int i = 1; i < rows - 1; ++i) {
      for (int j = 1; j < cols - 1; ++j) {
        const int value = a[i * cols + j];
        bool is_max = true;
        for (int di = -1; di <= 1 && is_max; ++di) {
          for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) {
              continue;
            }
            if (a[(i + di) * cols + (j + dj)] >= value) {
              is_max = false;
              break;
            }
          }
        }
        if (is_max) {
          ++result;
        }
      }
    }
    return result;
  }

  void process(const int *data, int rows, int cols, std::ofstream &out)
  {
    if (rows == 0 || cols == 0) {
      out << "0 0";
    } else {
      out << countLocalMax(data, rows, cols);
    }
    out << '\n';
  }

}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return kiriukhin::kBadArgs;
  }

  int mode = 0;
  if (std::strcmp(argv[1], "1") == 0) {
    mode = 1;
  } else if (std::strcmp(argv[1], "2") == 0) {
    mode = 2;
  } else {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return kiriukhin::kBadArgs;
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Error: cannot open input file\n";
    return kiriukhin::kBadInput;
  }

  int rows = 0;
  int cols = 0;
  if (!kiriukhin::readDimensions(in, rows, cols)) {
    std::cerr << "Error: input is empty or is not a matrix\n";
    return kiriukhin::kBadInput;
  }
  const long long count = static_cast< long long >(rows) * cols;

  std::ofstream out(argv[3]);
  if (!out) {
    std::cerr << "Error: cannot open output file\n";
    return kiriukhin::kBadArgs;
  }

  if (mode == 1) {
    if (count > kiriukhin::kMaxStaticSize) {
      std::cerr << "Error: matrix is too large for fixed-size array\n";
      return kiriukhin::kBadInput;
    }
    int data[kiriukhin::kMaxStaticSize];
    if (!kiriukhin::readElements(in, data, count)) {
      std::cerr << "Error: input is not a valid matrix\n";
      return kiriukhin::kBadInput;
    }
    kiriukhin::process(data, rows, cols, out);
  } else {
    int *const data = new int[count];
    if (!kiriukhin::readElements(in, data, count)) {
      delete[] data;
      std::cerr << "Error: input is not a valid matrix\n";
      return kiriukhin::kBadInput;
    }
    kiriukhin::process(data, rows, cols, out);
    delete[] data;
  }

  return kiriukhin::kOk;
}
