#include <iostream>
#include <stdexcept>

void exponent(int variable, int& local_max_variable, int& count_local_max_variable, int& last_trend);

namespace bulgakov
{
  constexpr int INVALID_INPUT_ERROR = 1;
  constexpr int CALCULATION_ERROR = 2;
}

int main()
{
  int last_trend = 0;
  int total_count = 0;
  int count_local_max_variable = 0;
  int local_max_variable = 0;

  try
  {
    bool reached_zero = false;
    int variable = 0;

    while (std::cin >> variable)
    {
      if (variable == 0)
      {
        reached_zero = true;
        break;
      }
      if (total_count == 0)
      {
        local_max_variable = variable;
      }
      total_count++;
      exponent(variable, local_max_variable, count_local_max_variable, last_trend);
    }

    if (!reached_zero)
    {
      throw std::runtime_error("ERROR: Invalid input data!");
    }
    if (total_count == 0)
    {
      throw std::length_error("ERROR: Sequence is empty!");
    }
    if (total_count >= 2 && last_trend == 1)
    {
      count_local_max_variable++;
    }
  }
  catch (const std::range_error& ex)
  {
    std::cerr << ex.what() << "\n";
    return bulgakov::CALCULATION_ERROR;
  }
  catch (const std::runtime_error& ex)
  {
    std::cerr << ex.what() << "\n";
    return bulgakov::INVALID_INPUT_ERROR;
  }
  catch (const std::length_error& ex)
  {
    std::cerr << ex.what() << "\n";
    return 2;
  }

  std::cout << count_local_max_variable << "\n";
  return 0;
}

void exponent(int variable, int& local_max_variable, int& count_local_max_variable, int& last_trend)
{
  int current_trend = 0;

  if (variable > local_max_variable)
  {
    current_trend = 1;
  }
  else if (variable < local_max_variable)
  {
    current_trend = -1;
  }

  if (current_trend != 0)
  {
    if (last_trend == 1 && current_trend == -1)
    {
      count_local_max_variable++;
    }
    last_trend = current_trend;
  }
  local_max_variable = variable;
}

