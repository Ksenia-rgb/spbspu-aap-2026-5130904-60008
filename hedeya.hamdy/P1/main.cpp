#include<iostream>
#include <algorithm>

int getLengthOfLongestRepeatingSubstring(std::string string);

int main()
{
    std::string string = "";
    std::cout << "Enter a string of characters: \n";
    std::cin >> string;

    int length = getLengthOfLongestRepeatingSubstring(string);
    std::cout << "Length of longest repeating substring: " << length;

    return EXIT_SUCCESS;
}

int getLengthOfLongestRepeatingSubstring(std::string string)
{
    int longest = 0, length = 0;
    int current = 0, previous = 0;

    for(int i = 1; i < string.length(); i++){
        current = string[i];
        previous = string[i - 1];

        length += 1;
        
        if(current != previous){
            length = 1;
        }

        longest = std::max(length, longest);
    }

    return longest;
}