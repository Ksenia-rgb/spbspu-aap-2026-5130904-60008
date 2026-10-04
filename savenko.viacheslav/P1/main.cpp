#include <iostream>

int processASequence();

int main() {
  int answer = 0;

  try {
    answer = processASequence();

    std::cout << "Number of local minima in the sequence: " << answer << "\n";

    return 0;
  }

  catch (int error_code) {
    return error_code;
  }
}

int processASequence() {
  int previous_number = 0;
  int current_number = 0;
  int next_number = 0;
  int count = 0;

  const int error_not_sequence = 1;
  const int error_too_short = 2;

  if (!(std::cin >> previous_number)) {
    std::cerr << "The input data cannot be identified as a sequence." << "\n";
    throw error_not_sequence;
  }

  if (previous_number == 0) {
    std::cerr << "The sequence is too short." << "\n";
    throw error_too_short;
  }

  if (!(std::cin >> current_number)) {
    std::cerr << "The input data cannot be identified as a sequence." << "\n";
    throw error_not_sequence;
  }

  if (current_number == 0) {
    return 0;
  }

  else {
    while (true) {
      if (!(std::cin >> next_number)) {
        std::cerr << "The input data cannot be identified as a sequence."
                  << "\n";
        throw error_not_sequence;
      }

      if (next_number == 0) {
        return count;
        break;
      }

      if (current_number < previous_number) {
        if (current_number < next_number) {
          count += 1;
        }
      }

      previous_number = current_number;
      current_number = next_number;
    }
  }
}
