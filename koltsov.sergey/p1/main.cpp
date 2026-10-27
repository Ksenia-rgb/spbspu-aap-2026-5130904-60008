#include <clocale>
#include <iostream>
#include <string>

namespace koltsov
{
  int countIncreasingElements()
  {
    int prev_num = 0;
    int curr_num = 0;
    int count = 0;

    const int err_invalid_input = 1;
    const std::string msg_invalid_input = "не последовательность";

    if (!(std::cin >> prev_num))
    {
      std::cerr << msg_invalid_input << "\n";
      throw err_invalid_input;
    }

    if (prev_num == 0)
    {
      return 0;
    }

    while (true)
    {
      if (!(std::cin >> curr_num))
      {
        std::cerr << msg_invalid_input << "\n";
        throw err_invalid_input;
      }

      if (curr_num == 0)
      {
        return count;
      }

      if (curr_num > prev_num)
      {
        count += 1;
      }

      prev_num = curr_num;
    }
  }
}

int main()
{
  setlocale(LC_ALL, "ru_RU.UTF-8");

  int result = 0;

  try
  {
    result = koltsov::countIncreasingElements();
    std::cout << result << "\n";
    return 0;
  }
  catch (int error_code)
  {
    return error_code;
  }
}
