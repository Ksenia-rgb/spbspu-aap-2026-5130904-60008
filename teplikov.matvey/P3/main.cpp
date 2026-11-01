#include <iostream>
#include <string>
#include <cctype>  // для isdigit проверки
#include <fstream>
#include <stdexcept>
#include <climits>

namespace teplikov
{
    const std::string NOT_EN_ARG = "Not enough arguments";
    const std::string TO_MAN_ARG = "Too many arguments";
    const std::string FR_PARAM_OUT_RNG = "First parameter is out of range";
    const std::string FR_PARAM_NOT_NUM = "First parameter is not a number";
    const std::string INV_VAL = "Invalid matrix data";

    constexpr int EXIT_SUCCESS_CODE = 0;
    constexpr int BAD_ARGS = 1;
    constexpr int BAD_DATA = 2;
    constexpr int LEN = 10000;

    int changeStaticArr(std::ifstream &input, std::ofstream &output, int row, int col);
    int changeDynamicArray(std::ifstream &input, std::ofstream &output, int row, int col);
    void increase(int *arr, int row, int col);
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << teplikov::NOT_EN_ARG << "\n";  // проверка на 4 аргумента
        return teplikov::BAD_ARGS;
    }

    if (argc > 4)
    {
        std::cerr << teplikov::TO_MAN_ARG << "\n";  // проверка на 4 аргумента
        return teplikov::BAD_ARGS;
    }

    if (!(std::isdigit(std::string(argv[1])[0])) || std::string(argv[1]).length() != 1)
    {    // проверка что argv[1] - однозначное число
        std::cerr << teplikov::FR_PARAM_NOT_NUM << "\n";
        return teplikov::BAD_ARGS;
    }

    if (std::string(argv[1]) != "1" && std::string(argv[1]) != "2")
    {  // проверка что это число либо 1 либо 2
        std::cerr << teplikov::FR_PARAM_OUT_RNG << "\n";
        return teplikov::BAD_ARGS;
    }

    std::ifstream input(argv[2]);
    std::ofstream output(argv[3]);

    int row = 0, col = 0, rz = 0;

    if (!input || !output)
    {
        std::cerr << teplikov::INV_VAL << "\n";
        return teplikov::BAD_DATA;
    }

    try
    {
        if (!(input >> row >> col)  row < 0  col < 0)
        {
            throw std::invalid_argument(teplikov::INV_VAL);
        }
        if (std::string(argv[1]) == "1")
        {
            rz = teplikov::changeStaticArr(input, output, row, col);
        }
        else
        {
            rz = teplikov::changeDynamicArray(input, output, row, col);
        }
    }
    catch (const std::invalid_argument &exspt)
    {
        std::cerr << "Invalid_argument: " << exspt.what() << "\n";
        return teplikov::BAD_DATA;
    }
    catch (const std::bad_alloc &)
    {
        std::cerr << "Memory allocation failed\n";
        return teplikov::BAD_DATA;
    }

    return teplikov::EXIT_SUCCESS_CODE;
}

namespace teplikov
{
    int changeStaticArr(std::ifstream &input, std::ofstream &output, int row, int col)
    {
        if (row != 0 && col > LEN / row)
        {
            throw std::invalid_argument(INV_VAL);
        }

        int arr[LEN] = {0};

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (!(input >> arr[i * col + j]))
                {
                    throw std::invalid_argument(INV_VAL);
                }
            }
        }

        int extraNum = 0;
        if (input >> extraNum)
        {
            throw std::invalid_argument(INV_VAL);
        }

        increase(arr, row, col);

        output << row << " " << col;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                output << " " << arr[i * col + j];
            }
        }
        output << "\n";

        return 0;
    }

    int changeDynamicArray(std::ifstream &input, std::ofstream &output, int row, int col)
    {
        if (row < 0  col < 0  (col != 0 && row > INT_MAX / col))
        {
            throw std::invalid_argument(INV_VAL);
        }

        if (row == 0 || col == 0)
        {
            output << row << " " << col << "\n";
            return 0;
        }

        int *const arr = new int[row * col]{0};

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (!(input >> arr[i * col + j]))
                {
                    delete[] arr;
                    throw std::invalid_argument(INV_VAL);
                }
            }
        }

        int extraNum = 0;
        if (input >> extraNum)
        {
            delete[] arr;
            throw std::invalid_argument(INV_VAL);
        }

        increase(arr, row, col);

        output << row << " " << col;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                output << " " << arr[i * col + j];
            }
        }
        output << "\n";

        delete[] arr;

        return 0;
    }

    void increase(int *arr, int row, int col)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                int top = i;
                int bott = row - 1 - i;
                int left = j;
                int right = col - 1 - j;

                int vMin = (top < bott) ? top : bott;
                int hMin = (left < right) ? left : right;
                int minBordDst = (vMin < hMin) ? vMin : hMin;

                arr[i * col + j] += (minBordDst + 1);
            }
        }
    }
}
