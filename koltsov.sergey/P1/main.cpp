#include <iostream>
#include <string>
#include <clocale>

int CountIncreasingElement();

int main()
{
  setlocale(LC_ALL, "ru_RU.UTF-8");

  int result = 0;

  try
  {
     result = CountIncreasingElement();
     std::cout << "количество элементво больших предыдущего " << result << "\n";
     return 0;
  }
  catch (int error_code)
    {
        return error_code;
    }
}

int CountIncreasingElement()
{
  int prev_num = 0;
  int curr_num = 0;
  int count = 0;

  const int err_invalid_input = 1;
  const std::string msg_invalid_input = "Входные данные не последовательность";

  if (!(std::cin >> prev_num))
  {
     std::cerr << msg_invalid_input << "\n";
     throw err_invalid_input;
  }
  while (true)
  {
     if (!(std::cin >> curr_num))
     {
       break;
     }
     if (curr_num > prev_num)
     {
        count += 1;
     }
     prev_num = curr_num;
  }
  return count;
}

