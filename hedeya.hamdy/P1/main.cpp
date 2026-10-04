#include<iostream>
#include <algorithm>

/*
Test Cases:
144222440 Expects output (return code 0): 3
10 Expects output (return code 0): 1
0 Expects output (return code 0): 0
*/

int main()
{
    std::string string = "";
    std::cout << "Enter a string of characters: \n";
    std::cin >> string;

    int longest = 0, length = 0;

    for(int i = 1; i < string.length(); i++){
        int current = string[i];
        int previous = string[i - 1];

        if(current == previous){
            length += 1;
        } else {
            length = 1;
        }

        longest = std::max(length, longest);
    }

    std::cout << "Length of longest substring of repeating characters: " << longest;
    return EXIT_SUCCESS;
}