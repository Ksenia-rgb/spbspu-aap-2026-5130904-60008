#include <iostream>
#include <fstream>

namespace kilyan
{
    const int MAX_STATIC_ELEMENTS = 10000;
    const int SUCCESS = 0;
    const int ARGUMENT_ERROR = 1;
    const int INPUT_ERROR = 2;
    int ReadDimensions(std::ifstream& infile, int& rows, int& cols)
    {
        if (!(infile >> rows >> cols))
        {
            std::cerr << "Error";
            return 2;
        }
        return 0;
    }

    int ReadElements(std::ifstream& infile, int* matrix_ptr, int rows, int cols)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (!(infile >> matrix_ptr[i * cols + j]))
                {
                    std::cerr << "Error";
                    return 2;
                }
            }
        }
        return 0;
    }

    int CountSaddlePoints(const int* matrix_ptr, int rows, int cols)
    {
        int saddle_count = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int current = matrix_ptr[i * cols + j];
                bool is_min_in_row = true;
                for (int k = 0; k < cols; ++k)
                {
                    if (current > matrix_ptr[i * cols + k])
                    {
                        is_min_in_row = false;
                        break;
                    }
                }
                bool is_max_in_col = true;
                if (is_min_in_row)
                {
                    for (int k = 0; k < rows; k++)
                    {
                        if (current < matrix_ptr[k * cols + j])
                        {
                            is_max_in_col = false;
                            break;
                        }
                    }
                }
                if (is_min_in_row && is_max_in_col)
                {
                    saddle_count++;
                }
            }
        }
        return saddle_count;
    }

    int WriteResault(std::ofstream& outfile, int result)
    {
        outfile << result << "\n";
        if (!outfile)
        {
            std::cerr << "Error\n";
            return 1;
        }
        return 0;
    }

    int RunFixed(std::ifstream& infile, std::ofstream& outfile)
    {
        int rows = 0, cols = 0;
        int status = ReadDimensions(infile, rows, cols);
        if (status != 0) return status;
        int static_matrix[10000];
        if (rows * cols > 10000)
        {
            std::cerr << "Error\n";
            return 2;
        }
        status = ReadElements(infile, static_matrix, rows, cols);
        if (status != 0) return status;
        int extra_element;
        if (infile >> extra_element)
        {
            std::cerr << "Error\n";
            return 2;
        }
        int result = CountSaddlePoints(static_matrix, rows, cols);
        return WriteResault(outfile, result);
    }

    int RunDynamic(std::ifstream& infile, std::ofstream& outfile)
    {
        int rows = 0, cols = 0;
        int status = ReadDimensions(infile, rows, cols);
        if (status != 0) return status;
        int* dynamic_matrix = new int[rows * cols];
        status = ReadElements(infile, dynamic_matrix, rows, cols);
        if (status != 0)
        {
            delete[] dynamic_matrix;
            return status;
        }
        int extra_element;
        if (infile >> extra_element)
        {
            std::cerr << "Error\n";
            delete[] dynamic_matrix;
            return 2;
        }
        int result = CountSaddlePoints(dynamic_matrix, rows, cols);
        int write_status = WriteResault(outfile, result);

        delete[] dynamic_matrix;
        return write_status;
    }
}
int main(int argc, char* argv[])
{
    if (argc != 4 || *argv[1] == '\0' || *(argv[1] + 1) != '\0')
    {
        std::cerr << "Error";
        return 1;
    }
    char mode = *argv[1];
    std::ifstream input(argv[2]);
    if (!input)
    {
        std::cerr << "Error";
        return 2;
    }
    std::ofstream output(argv[3]);
    if (!output)
    {
        std::cerr << "Error";
        return 1;
    }
    int status = 0;
    switch (mode)
    {
    case '1':
        status = kilyan::RunFixed(input, output);
        break;
    case '2':
        status = kilyan::RunDynamic(input, output);
        break;
    default:
        std::cerr << "Error";
        return 2;
        break;
    }
    return status;
}