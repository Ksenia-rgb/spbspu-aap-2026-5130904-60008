#include <iostream>
#include <stdexcept>

namespace dumina {

  constexpr int invalid_data_exit_code = 1;
  const char invalid_input_message[] = "INVALID INPUT";

  int calcSuitElemCount();
}
int main()
{
  try {
    std::cout << dumina::calcSuitElemCount() << '\n';
  } catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << '\n';
    return dumina::invalid_data_exit_code;
  }
  return 0;
}

int dumina::calcSuitElemCount()
{
  int prev_el = 0;
  int cur_el = 0;
  int next_el = 0;
  int suit_el_count = 0;

  if (!(std::cin >> prev_el)) {
    throw std::invalid_argument(dumina::invalid_input_message);
  }

  if (prev_el == 0) {
    return 0;
  }

  if (!(std::cin >> cur_el)) {
    throw std::invalid_argument(dumina::invalid_input_message);
  }

  if (cur_el == 0) {
    return 0;
  }

  while (true) {
    if (!(std::cin >> next_el)) {
      throw std::invalid_argument(dumina::invalid_input_message);
    }

    if (next_el == 0) {
      break;
    }
    if (cur_el < prev_el && cur_el > next_el) {
      suit_el_count++;
    }
    prev_el = cur_el;
    cur_el = next_el;
  }
  return suit_el_count;
}
