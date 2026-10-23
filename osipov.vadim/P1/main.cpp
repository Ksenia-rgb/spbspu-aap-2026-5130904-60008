#include <iostream>


int main()
{
  int cifra = 0;
  int posledovatelnost[10000];
  int posledovatelnost_size = 0;
  int otvet[10000];
  int otvet_size = 0;
  int streak = 1;

  while (true) {
    if (!(std::cin >> cifra)) {
      std::cerr << "its not a number\n";
      return 1;
    }

    if (cifra == 0) {
      break;
    }

    posledovatelnost[posledovatelnost_size] = cifra;
    posledovatelnost_size++;
  }

  if (posledovatelnost_size == 0) {
    std::cout << 0 << "\n";
    return 0;
  }
  int i = 0;
  while (i < posledovatelnost_size - 1) {
    if (posledovatelnost[i] <= posledovatelnost[i + 1]) {
      streak++;
    } else {
      otvet[otvet_size] = streak;
      otvet_size++;
      streak = 1;
    }
    i++;
  }

  otvet[otvet_size] = streak;
  otvet_size++;

  int max_streak = otvet[0];
  for (int k = 1; k < otvet_size; k++) {
    if (otvet[k] > max_streak) {
      max_streak = otvet[k];
    }
  }
  std::cout << max_streak << "\n";

 return 0;
}
