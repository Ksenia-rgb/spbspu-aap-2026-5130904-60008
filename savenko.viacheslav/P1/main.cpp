#include <iostream>

int process_a_sequence();

int main()
{
    int answer=0;

    try
    {
        answer=process_a_sequence();

        std::cout << "Number of local minima in the sequence: " << answer << "\n";

        return 0;
    }

    catch (int error_code)
    {
        return error_code;
    }
}

int process_a_sequence()
{
    int previous_number=0;
    int current_number=0;
    int next_number=0;
    int count=0;

    if (!(std::cin >> previous_number))
    {
        std::cerr << "The input data cannot be identified as a sequence." << "\n";
        throw 1;
    }

    if (previous_number==0)
    {
        std::cerr << "The sequence is too short." << "\n";
        throw 2;
    }

    if (!(std::cin >> current_number))
    {
        std::cerr << "The input data cannot be identified as a sequence." << "\n";
        throw 1;
    }

    if (current_number==0)
    {
        return 0;
    }

    else
    {
        while (true)
        {
            if (!(std::cin >> next_number))
            {
                std::cerr << "The input data cannot be identified as a sequence." << "\n";
                throw 1;
            }

            if (next_number==0)
            {
                return count;
                break;
            }

            if (current_number<previous_number)
            {
                if (current_number<next_number)
                {
                    count+=1;
                }
            }

            previous_number=current_number;
            current_number=next_number;
        }
    }
}
