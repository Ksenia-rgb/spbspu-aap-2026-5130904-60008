#include <iostream>
#include <limits>
#include <cstring>
#include <cctype>
#include <cstddef>
#include <new>

namespace stremetskiy
{
	constexpr int SUCCESS_CODE = 0;
	constexpr int FAIL_CODE = 1;
	constexpr std::size_t MAX_SIZE_T = std::numeric_limits<std::size_t>::max();

	char *readLine(std::istream &);
	char *deleteLatSymb(const char *, char *) noexcept;
}

int main()
{
	char *input = nullptr;
	char *result = nullptr;

	try
	{
		input = stremetskiy::readLine(std::cin);

		if (input == nullptr)
		{
			std::cerr << "Cannot allocate input buffer\n";
			return stremetskiy::FAIL_CODE;
		}

		if (std::cin.bad())
		{
			delete[] input;
			std::cerr << "Input error\n";
			return stremetskiy::FAIL_CODE;
		}

		const std::size_t length = std::strlen(input);
		result = new (std::nothrow) char[length + 1];

		if (result == nullptr)
		{
			delete[] result;
			delete[] input;
			std::cerr << "Cannot allocate result buffer\n";
			return stremetskiy::FAIL_CODE;
		}

		stremetskiy::deleteLatSymb(input, result);

		std::cout << result << '\n';

		delete[] result;
		delete[] input;
		return stremetskiy::SUCCESS_CODE;
	}
	catch (const std::bad_alloc &)
	{
		delete[] result;
		delete[] input;
		std::cerr << "Not enough memory\n";
		return stremetskiy::FAIL_CODE;
	}
}

namespace stremetskiy
{
	char *readLine(std::istream &input)
	{
		char *data = nullptr;
		std::size_t capacity = 8;
		std::size_t size = 0;
		char ch = '\0';

		try
		{
			data = new (std::nothrow) char[capacity];

			if (data == nullptr)
			{
				throw;
			}

			while (input.get(ch) && ch != '\n')
			{
				if (size == capacity - 1)
				{
					if (capacity > (stremetskiy::MAX_SIZE_T / 2))
					{
						delete[] data;
						throw;
					}

					const std::size_t newCapacity = capacity * 2;
					char *expandedData = new (std::nothrow) char[newCapacity];
					if (expandedData == nullptr)
					{
						delete[] data;
						throw;
					}

					for (std::size_t i = 0; i < size; i++)
					{
						expandedData[i] = data[i];
					}

					delete[] data;
					data = expandedData;
					capacity = newCapacity;
				}
				data[size++] = ch;
			}

			data[size] = '\0';
			return data;
		}
		catch (...)
		{
			delete[] data;
			throw;
		}
	}

	char *deleteLatSymb(const char *inp, char *res) noexcept
	{
		std::size_t j = 0;

		for (std::size_t i = 0; inp[i] != '\0'; i++)
		{
			unsigned char ch = static_cast<unsigned char>(inp[i]);
			if (ch < 128 && std::isalpha(ch))
			{
				continue;
			}
			res[j++] = inp[i];
		}
		res[j] = '\0';
		return res;
	}
}
