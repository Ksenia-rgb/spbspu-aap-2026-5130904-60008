#include <iostream>
#include <climits> // Библиотека для получения макс. значения int
#include <stdexcept> // Библиотека для получении сообщения ошибки

int main()
{
  setlocale(LC_ALL, "rus");

  int num = -1;
  int count_max = 0;
  int max = INT_MIN;
  int size = 0;

  std::cout
  << "\nВведите последовательность чисел через пробел,"
  << "последнее число должно являться 0: \n";

  try
  {
    while (num != 0)
    {
      if (!(std::cin >> num))
      {
        throw std::invalid_argument("Неверный ввод");
      }

      if (num == 0 && size == 0)
      {
        throw std::logic_error("Слишком маленькая последовательность");
      }

      if (num > max)
      {
        max = num;
        count_max = 1;
      }
      else if (num == max)
      {
        if (size < INT_MAX)
        {
          ++count_max;
        }
        else
        {
          throw std::range_error("Слишком большая последовательность");
        }
      }
      ++size;
    }
  }

  catch (const std::invalid_argument & ex)
  {
    std::cerr << "Invalid input: " << ex.what() << "\n";
    return 1;
  }

  catch (const std::logic_error & ex)
  {
   std::cerr << "Invalid input: " << ex.what() << "\n";
    return 2;
  }

  catch (const std::range_error & ex)
  {
    std::cerr << "Value out of range: " << ex.what() << "\n";
    return 2;
  }

  catch (...)
  {
    std::cerr << "Не тут что другое \n";
    return 2;
  }

  std::cout
  << "Количество максимальных чисел последовательности: "
  << count_max << "\n";
  return 0;
}
