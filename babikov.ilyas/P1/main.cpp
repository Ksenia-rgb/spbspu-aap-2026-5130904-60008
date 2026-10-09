#include <exception>
#include <iostream>
#include <stdexcept>

int main() {
  int current = 0;
  int previous = 0;
  int ans = 0;
  int count = 0;

  std::cout << "Введите последовательность целых чисел"
            << "(0 для завершения):\n";

  try {
    while (true) {

      if (!(std::cin >> current)) {

        throw std::runtime_error("Некорректные входные данные");
      }

      if (current == 0) {

        break;
      }

      if (count > 0) {

        if ((current > 0 && previous < 0) || (current < 0 && previous > 0)) {
          ++ans;
        }
      }

      previous = current;
      ++count;
    }
  }

  catch (const std::exception &) {
    std::cerr << "Ошибка: входные данные не являются"
              << "последовательностью целых чисел\n";
    return 1;
  }

  if (count < 2) {
    std::cerr << "Ошибка: недостаточно элементов"
              << "для подсчёта смен знака\n";
    return 2;
  }

  std::cout << ans << "\n";

  return 0;
}
