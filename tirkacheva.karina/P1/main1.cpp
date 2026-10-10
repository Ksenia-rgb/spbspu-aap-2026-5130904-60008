#include <iostream>
#include <stdexcept>

int countDivisible();

int main()
{
  try {
    std::cout << countDivisible() << "\n";

    return 0;
  } catch (const std::invalid_argument &error) {
    std::cerr << "Error: " << error.what() << "\n";

    return 2;
  }
}
int countDivisible()
{
  int previous = 0;
  int current = 0;
  int count = 0;
  int elements = 0;

  if (!(std::cin >> previous)) {
    throw std::invalid_argument("Empty sequence");
  }

  if (previous == 0) {
    throw std::invalid_argument("Empty sequence");
  }

  elements = 1;

  while (std::cin >> current) {
    if (current == 0) {
      break;
    }

    elements++;

    if (current % previous == 0) {
      count++;
    }

    previous = current;
  }

  if (elements < 2) {
    throw std::invalid_argument("Not enough elements");
  }

  return count;
}
