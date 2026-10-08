#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        int previous;
        int current;
        int count = 0;
        int elements = 0;

        std::cin >> previous;

        if (previous == 0)
        {
            throw std::invalid_argument("Empty sequence");
        }

        elements = 1;

        while (std::cin >> current)
        {
            if (current == 0)
            {
                break;
            }

            elements++;

            if (current % previous == 0)
            {
                count++;
            }

            previous = current;
        }

        if (elements < 2)
        {
            throw std::invalid_argument("Not enough elements");
        }

        std::cout << count << "\n";

        return 0;
    }
    catch (const std::invalid_argument& error)
    {
        std::cerr << "Error: " << error.what() << "\n";

        return 2;
    }
}
