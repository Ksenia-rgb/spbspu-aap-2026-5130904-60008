#include <iostream>

int readInt();

int main()
{
  try
  {
    int curr_len = 1;
    int max_len = 1;
    int prev = 0;
    int now = 0;

    prev = readInt();

    if (prev == 0)
    {
      std::cout << "0\n";
      return 0;
    }

    while (true)
    {
      now = readInt();

      if (now == 0)
        {
          if (curr_len > max_len)
          {
            max_len = curr_len;
          }
          break;
        }

      if (now >= prev)
      {
        ++curr_len;
      }

      else
      {
        if (curr_len > max_len)
        {
          max_len = curr_len;
        }
        curr_len = 1;
      }

      prev = now;
    }

    std::cout << max_len << "\n";

    return 0;
  }

  catch (int error_code)
  {
    return error_code;
  }
}

int readInt()
{
  const int invalid_input = 1;

  int value = 0;
  if (!(std::cin >> value))
  {
    std::cerr << "Invalid Input\n";
    throw invalid_input;
  }
  return value;
}
