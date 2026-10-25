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

}

bool isInteger(const char* s)
{
    int i = 0;
    if (s[0] == '+'  s[0] == '-') i++;
    if (s[i] == '\0') return false;
    for (; s[i] != '\0'; i++)
    {
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

bool readHeader(std::ifstream& in, int& rows, int& cols)
{
    if (!(in >> rows >> cols)) return false;
    if (rows < 0  cols < 0) return false;
    return true;
}

bool readElements(std::ifstream& in, int* a, long long count)
{
    for (long long i = 0; i < count; i++)
    {
        if (!(in >> a[i])) return false;
    }
    int extra;
    if (in >> extra) return false;
    in.clear();
    in >> std::ws;
    if (!in.eof()) return false;
    return true;
}

void process(int* a, int r, int c)
{
    int top = 0, bottom = r - 1, left = 0, right = c - 1;
    int k = 1;
    while (top <= bottom && left <= right) {
        for (int i = bottom; i >= top; i--) a[i * c + left] -= k++;
        left++;
        if (left > right) break;

        for (int j = left; j <= right; j++) a[top * c + j] -= k++;
        top++;
        if (top > bottom) break;

        for (int i = top; i <= bottom; i++) a[i * c + right] -= k++;
        right--;
        if (left > right) break;

        for (int j = right; j >= left; j--) a[bottom * c + j] -= k++;
        bottom--;
    }
}

bool writeResult(const char* name, const int* a, int r, int c)
{
    std::ofstream out(name);
    if (!out) return false;
    out << r << ' ' << c;
    for (long long i = 0; i < static_cast<long long>(r) * c; i++) out << ' ' << a[i];
    out << '\n';
    return static_cast<bool>(out);
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
    int num;
    if (std::strcmp(argv[1], "1") == 0) {
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

    int rows, cols;

    if (!readHeader(in, rows, cols))
    {
        std::cerr << inashevskiy::NOT_MAT_IN_FILE;
        return inashevskiy::MAT_EXIT_CODE;
    }
    long long count = static_cast<long long>(rows) * cols;

    if (num == 1)
    {
        int fixedArr[10000];

        if (count > 10000)
        {
            std::cerr << inashevskiy::NOT_MAT_IN_FILE;
            return inashevskiy::MAT_EXIT_CODE;
        }
        if (!readElements(in, fixedArr, count))
        {
            std::cerr << inashevskiy::NOT_MAT_IN_FILE;
            return inashevskiy::MAT_EXIT_CODE;
        }
        process(fixedArr, rows, cols);
        if (!writeResult(argv[3], fixedArr, rows, cols))
        {
            std::cerr << inashevskiy::INCOR_FILE_NAME;
            return inashevskiy::ARG_EXIT_CODE;
        }
    }
    else
    {
        int* dyn = new int[count > 0 ? count : 1];
        if (!readElements(in, dyn, count))
        {
            std::cerr << inashevskiy::NOT_MAT_IN_FILE;
            delete[] dyn;
            return inashevskiy::MAT_EXIT_CODE;
        }
        process(dyn, rows, cols);
        bool ok = writeResult(argv[3], dyn, rows, cols);
        delete[] dyn;
        if (!ok)
        {
            std::cerr << inashevskiy::INCOR_FILE_NAME;
            return inashevskiy::ARG_EXIT_CODE;
        }
    }
    return 0;
}
