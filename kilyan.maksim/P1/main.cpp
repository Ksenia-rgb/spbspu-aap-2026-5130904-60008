#include <iostream>

int main()
{
	int currentNumber = 0;
	int previsionNumber = 0;
	int cnt = 0;
	bool isFirst = true;

	if (!(std::cin >> currentNumber))
	{
		std::cerr << "Invalid input.\n";
		return 1;
	}

	while (currentNumber != 0)
	{
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
		if (!(std::cin >> currentNumber))
		{
			std::cerr << "Invalid input.\n";
			return 1;
		}
	}
	std::cout << cnt << "\n";
	return 0;
}
