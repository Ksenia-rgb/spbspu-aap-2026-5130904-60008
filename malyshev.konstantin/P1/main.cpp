#include <iostream>



int main()

{

    int a = 1;

    int b = 0;

    int c = 0;

    int count = 0;



    while (a != 0)

    {

        try

        {

            if (!(std::cin >> a))

            {

                throw 1;

            }



            if (a == 0)

            {

                if (count < 2)

                {

                    throw 2;

                }

                break;

            }



            if (count >= 1)

            {

                if (a % b == 0)

                {

                    c += 1;

                }

            }



            count += 1;

            b = a;

        }



        catch (int thr)

        {

            if (thr == 1)

            {

                std::cerr << "Error: Input is not a number";

                return 1;

            }

            if (thr == 2)

            {

                std::cerr << "Error: Sequence must contain at least 2 elements";

                return 2;

            }

        }

    }

    std::cout << c << "\n";

    return 0;

}
