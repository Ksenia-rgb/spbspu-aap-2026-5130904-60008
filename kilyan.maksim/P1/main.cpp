#include <iostream>

namespace kilyan
{
	bool isValidInput()
	{
		if (std::cin.fail())
		{
			return false;
		}
		char nextChar = std::cin.peek();
		if (nextChar != ' ' && nextChar != '\n' && nextChar != '\t')
		{
			return false;
		}
		return true;
	}
}
int main()
{
	int currentNumber = 0;
	int previsionNumber = 0;
	int cnt = 0;
	bool isFirst = true;
	while (true)
	{
		std::cin >> currentNumber;
		if (!kilyan::isValidInput())
		{
			std::cerr << "Invalid input.";
			return 1;
		}
		if (currentNumber == 0)
		{
			break;
		}
		if (!isFirst)
		{
			if (currentNumber > previsionNumber)
			{
				cnt++;
			}
		}
		else
		{
			isFirst = false;
		}
		previsionNumber = currentNumber;
	}
	std::cout << cnt << std::endl;
	return 0;
}