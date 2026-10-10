#ifndef MAIN_CPP
#define MAIN_CPP

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

int getLengthOfLongestRepeatingSubstring(std::string string);

int main()
{
  std::string string;

  std::cout << "Enter a string of characters: \n";
  std::cin >> string;

  const int length = getLengthOfLongestRepeatingSubstring(string);
  std::cout << "Length of longest repeating substring: " << length;

  return EXIT_SUCCESS;
}

int getLengthOfLongestRepeatingSubstring(std::string string)
{
  int longest = 0;
  int length = 0;
  int current = 0;
  int previous = 0;

  for (int i = 1; i < static_cast< int >(string.length()); i++)
  {
    current = string[i];
    previous = string[i - 1];

    length += 1;

    if (current != previous)
    {
      length = 1;
    }

    longest = std::max(length, longest);
  }

  return longest;
}

#endif
