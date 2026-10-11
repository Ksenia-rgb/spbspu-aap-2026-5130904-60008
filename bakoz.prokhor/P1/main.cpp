#include <iostream>
#include <stdexcept>

namespace bakoz
{
  constexpr int INVALID_INPUT_ERROR = 1;
  bool hasSignChanged(int previous, int current);
}

int main()
{
  int current = 0;
  int previous = 0;
  int changed_signs = 0;
  bool has_previous = false;

  try
  {
    while (true)
    {
      if (!(std::cin >> current))
      {
        throw std::runtime_error("incorrect input data");
      }

      if (current == 0)
      {
        break;
      }

      if (has_previous && bakoz::hasSignChanged(previous, current))
      {
        ++changed_signs;
      }

      previous = current;
      has_previous = true;
    }
  }
  catch (const std::runtime_error& ex)
  {
    std::cerr << ex.what() << "\n";
    return bakoz::INVALID_INPUT_ERROR;
  }

  std::cout << changed_signs << "\n";

  return 0;
}

namespace bakoz
{
  bool hasSignChanged(int previous, int current)
  {
    return (previous < 0 && current > 0) || (previous > 0 && current < 0);
  }
}
