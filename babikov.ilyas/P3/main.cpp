#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <climits>
#include <new>
#include <stdexcept>

namespace babikov
{
  const std::string FEW_ARG = "Недостаточно аргументов";
  const std::string MANY_ARG = "Слишком много аргументов";
  const std::string OUT_RANGE = "Первый параметр вне допустимого диапазона";
  const std::string NOT_NUMBER = "Первый параметр не является числом";
  const std::string BAD_FILE = "Некорректное имя файла";
  const std::string NOT_MATRIX = "Файл не содержит корректную матрицу";
  const std::string NOT_MEMORY = "Недостаточно памяти для матрицы";

  const int ARG_CODE = 1;
  const int MATRIX_CODE = 2;
  const int BUFFER = 10000;

  struct Matrix
  {
    int rows;
    int cols;
    const int * data;
  };

  int getMode(const std::string & param);
  int readSize(std::ifstream & infile, int & rows, int & cols);
  bool readData(std::ifstream & infile, int * data, int count);
  int countColumns(const Matrix & mat);
  void runStatic(std::ifstream & infile, std::ofstream & outfile);
  void runDynamic(std::ifstream & infile, std::ofstream & outfile);
}

int main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << babikov::FEW_ARG << "\n";
    return babikov::ARG_CODE;
  }

  if (argc > 4)
  {
    std::cerr << babikov::MANY_ARG << "\n";
    return babikov::ARG_CODE;
  }

  int mode = 0;

  try
  {
    mode = babikov::getMode(argv[1]);
  }
  catch (const std::invalid_argument & ex)
  {
    std::cerr << ex.what() << "\n";
    return babikov::ARG_CODE;
  }

  std::ifstream infile(argv[2]);
  std::ofstream outfile(argv[3]);

  if (!infile.is_open() || !outfile.is_open())
  {
    std::cerr << babikov::BAD_FILE << "\n";
    return babikov::ARG_CODE;
  }

  try
  {
    if (mode == 1)
    {
      babikov::runStatic(infile, outfile);
    }
    else
    {
      babikov::runDynamic(infile, outfile);
    }
  }
  catch (const std::invalid_argument & ex)
  {
    std::cerr << ex.what() << "\n";
    return babikov::MATRIX_CODE;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << babikov::NOT_MEMORY << "\n";
    return babikov::MATRIX_CODE;
  }

  return 0;
}

int babikov::getMode(const std::string & param)
{
  bool is_number = !param.empty();

  for (const char c : param)
  {
    if (!std::isdigit(static_cast< unsigned char >(c)))
    {
      is_number = false;
    }
  }

  if (!is_number)
  {
    throw std::invalid_argument(babikov::NOT_NUMBER);
  }

  if (param == "1")
  {
    return 1;
  }

  if (param == "2")
  {
    return 2;
  }

  throw std::invalid_argument(babikov::OUT_RANGE);
}

int babikov::readSize(std::ifstream & infile, int & rows, int & cols)
{
  if (!(infile >> rows >> cols))
  {
    throw std::invalid_argument(babikov::NOT_MATRIX);
  }

  if (rows < 0 || cols < 0)
  {
    throw std::invalid_argument(babikov::NOT_MATRIX);
  }

  if (cols != 0 && rows > INT_MAX / cols)
  {
    throw std::invalid_argument(babikov::NOT_MATRIX);
  }

  return rows * cols;
}

bool babikov::readData(std::ifstream & infile, int * data, int count)
{
  for (int i = 0; i < count; ++i)
  {
    if (!(infile >> data[i]))
    {
      return false;
    }
  }

  return true;
}

int babikov::countColumns(const babikov::Matrix & mat)
{
  if (mat.rows == 0 || mat.cols == 0)
  {
    return 0;
  }

  int result = 0;

  for (int j = 0; j < mat.cols; ++j)
  {
    bool has_equal = false;

    for (int i = 0; i + 1 < mat.rows && !has_equal; ++i)
    {
      if (mat.data[i * mat.cols + j] == mat.data[(i + 1) * mat.cols + j])
      {
        has_equal = true;
      }
    }

    if (!has_equal)
    {
      ++result;
    }
  }

  return result;
}

void babikov::runStatic(std::ifstream & infile, std::ofstream & outfile)
{
  int rows = 0;
  int cols = 0;
  const int count = babikov::readSize(infile, rows, cols);

  if (count > babikov::BUFFER)
  {
    throw std::invalid_argument(babikov::NOT_MATRIX);
  }

  int data[babikov::BUFFER] = {0};

  if (!babikov::readData(infile, data, count))
  {
    throw std::invalid_argument(babikov::NOT_MATRIX);
  }

  const babikov::Matrix mat{rows, cols, data};
  outfile << babikov::countColumns(mat) << "\n";
}

void babikov::runDynamic(std::ifstream & infile, std::ofstream & outfile)
{
  int rows = 0;
  int cols = 0;
  const int count = babikov::readSize(infile, rows, cols);

  int * data = new int[count];
  const bool is_read = babikov::readData(infile, data, count);

  if (is_read)
  {
    const babikov::Matrix mat{rows, cols, data};
    outfile << babikov::countColumns(mat) << "\n";
  }

  delete[] data;

  if (!is_read)
  {
    throw std::invalid_argument(babikov::NOT_MATRIX);
  }
}
