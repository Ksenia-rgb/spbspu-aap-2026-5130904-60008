#include <iostream>
#include <string>

int char_povtor(const char* stroka, int razmer_stroki, char* sostav_povtora) noexcept;
void ubrat_povtor(char* sostav_povtora) noexcept;

int main() {
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
        std::cerr << "empty string" << "\n";
        return 1;
    }
    int razmer_stroki = input.size();
    char* stroka = new char[razmer_stroki + 1];
    for (int i = 0; i < razmer_stroki; ++i)
    {
        stroka[i] = input[i];
    }
    stroka[razmer_stroki] = '\0';
    char* sostav = new char[razmer_stroki + 1];
    char_povtor(stroka, razmer_stroki, sostav);
    ubrat_povtor(sostav);
    std::cout << sostav << '\n';
    delete[] stroka;
    delete[] sostav;

    return 0;
}

int char_povtor(const char* stroka, int razmer_stroki, char* sostav_povtora) noexcept {
    int count = 0;
    for (int i = 0; i < razmer_stroki; ++i) {
        for (int j = i + 1; j < razmer_stroki; ++j) {
            if (stroka[i] == stroka[j]) {
                sostav_povtora[count] = stroka[i];
                count++;
                break;
            }
        }
    }
    sostav_povtora[count] = '\0';
    return count;
}

void ubrat_povtor(char* sostav_povtora) noexcept {
    int element[10000] = { 0 };
    int write = 0;

    for (int read = 0; sostav_povtora[read] != '\0'; ++read) {
        unsigned char c = sostav_povtora[read];
        if (element[c] == 0) {
            sostav_povtora[write] = c;
            write++;
            element[c] = 1;
        }
    }
    sostav_povtora[write] = '\0';
}

