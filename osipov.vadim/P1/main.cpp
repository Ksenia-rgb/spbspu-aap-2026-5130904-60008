#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int cifra = 0;
    std::vector<int> posledovatelnoct;
    std::vector<int> otvet;
    int streak = 1;

    while (true) 
    {
        if (!(std::cin >> cifra)) 
        {
            std::cerr << "its not a number\n";
            return 1;
        }
        if (cifra == 0) 
        {
            break;
        }

        posledovatelnoct.push_back(cifra);
    }
    if (posledovatelnoct.empty()) 
    {
        std::cout << 0 << "\n";
        return 0;
    }

    int i = 0;
    while (i < posledovatelnoct.size())
    {
        if ((i + 1) == posledovatelnoct.size())
        {
            otvet.push_back(streak);
            std::cout << @id8251725 (*std)::max_element(otvet.begin(), otvet.end()) << std::endl;
            return 0;
        }
        if (posledovatelnoct[i] <= posledovatelnoct[i + 1])
        {
            streak++;
            i++;
        }
        else
        {
            otvet.push_back(streak);
            streak = 1;
            i++;
        }
    }

    return 0;
}
