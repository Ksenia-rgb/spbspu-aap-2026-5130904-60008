#include <iostream>
#include <fstream>
#include <string>

namespace malyshev {
	const int error_args = 1;
	const int error_data = 2;
	const int max_size = 10000;
	const std::string elements_more_10000 = "elements more 10000";

	int process_fix_massive(std::ifstream& ifile, int* matrix, int& rows, int& cols);
	int process_dynamic_massive(std::ifstream& ifile, int*& matrix, int& rows, int& cols);
	int long_ser_cols(int* matrix, int rows, int cols);
}

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr << "The number of command-line arguments does not match the specification "
			<< "or the first parameter cannot be interpreted "
			<< "as the indicated job numbers\n";
		return malyshev::error_args;
	}

	std::string num = argv[1];
	std::string input_filename = argv[2];
	std::string output_filename = argv[3];


	int rows = 0;
	int cols = 0;
	int res = 0;
	int read_status = 0;
	int static_matrix[10000];
	int* dynamic_matrix = nullptr;

	std::ifstream file(input_filename);
	
	if (file.fail())
	{
		std::cerr << "cannot be interpreted as a two-dimensional array "
			<< "or the file is empty\n";
		return malyshev::error_data;
	}

	if (num == "1")
	{
		read_status  = malyshev::process_fix_massive(file, static_matrix, rows, cols);
	}

	else if (num == "2")
	{
		read_status = malyshev::process_dynamic_massive(file, dynamic_matrix, rows, cols);
	}

	else
	{
		std::cerr << "The number of command-line arguments does not match the specification "
			<< "or the first parameter cannot be interpreted "
			<< "as the indicated job numbers\n";
		file.close();
		return malyshev::error_args;
	}

	file.close();

	if (read_status != 0) 
	{
		std::cerr << "cannot be interpreted as a two-dimensional array " 
			<< "or the file is empty\n";
		if (num == "2" && dynamic_matrix != nullptr) {
			delete[] dynamic_matrix;
		}
		return read_status;
	}

	if (num == "1")
	{
		res = malyshev::long_ser_cols(static_matrix, rows, cols);
	}
	else if (num == "2")
	{
		res = malyshev::long_ser_cols(dynamic_matrix, rows, cols);
	}

	std::ofstream outfile(output_filename);
	if (outfile.fail())
	{
		std::cerr << "The file was not saved\n";
		if (num == "2") {
			delete[] dynamic_matrix;
		}
		return malyshev::error_args;
	}

	outfile << res << "\n";
	outfile.close();

	if (num == "2") {
		delete[] dynamic_matrix;
	}
	return 0;
}

namespace malyshev{
	int process_fix_massive(std::ifstream& ifile, int* matrix, int& rows, int& cols)
	{
		ifile >> rows >> cols;
		if (ifile.fail()) 
		{
			return error_data;
		}
		if (rows * cols > max_size)
		{
			std::cerr << "elements more 10000\n";
			return error_data;
		}
		int total_el = rows * cols;
		for (size_t i = 0; i < total_el;i++)
		{
			ifile >> matrix[i];
			if (ifile.fail()) 
			{
				return error_data;
			}
		}
		char extra;
		ifile >> extra;
		if (!ifile.fail())
		{
			return error_data;
		}
		return 0;
	}

	int process_dynamic_massive(std::ifstream& ifile, int*& matrix, int& rows, int& cols)
	{
		ifile >> rows >> cols;
		if (ifile.fail())
		{
			return error_data;
		}
		if (rows < 0 || cols < 0) 
		{
			return error_data;
		}
		matrix = new int[rows * cols];
		int total_el = rows * cols;
		for (int i = 0; i < total_el; i++)
		{
			ifile >> matrix[i];
			if (ifile.fail())
			{
				return error_data;
			}
		}
		char extra;
		ifile >> extra;
		if (!ifile.fail())
		{
			return error_data;
		}
		return 0;
	}

	int long_ser_cols(int* matrix, int rows, int cols)
	{
		if (rows <= 0 || cols <= 0)
		{
			return 0;
		}

		int max_ser_len = 0;
		int max_cols = 0;

		for (size_t i = 0; i < cols; i++)
		{
			int current_sers = 1;
			int max_in_col = 1;

			for (size_t j = 1; j < rows; j++)
			{
				if (matrix[j * cols + i] == matrix[(j - 1) * cols + i])
				{
					current_sers++;
				}
				else
				{
					current_sers = 1;
				}
				if (current_sers > max_in_col)
				{
					max_in_col = current_sers;
				}
			}
			if (max_in_col > max_ser_len)
			{
				max_ser_len = max_in_col;
				max_cols = i + 1;
			}
		}
		return max_cols;
	}
}
