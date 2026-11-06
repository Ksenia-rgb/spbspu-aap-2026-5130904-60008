#include <iostream>
#include <cctype>
#include <cstddef>

namespace kilyan
{
    const int SUCCESS = 0;
    const int INPUT_ERROR = 1;
    char* removeExtraSpaces(const char* src, char* dst)
    {
        if (src == nullptr || dst == nullptr)
        {
            return dst;
        }
        size_t readIndex = 0;
        size_t writeIndex = 0;
        while (src[readIndex] != '\0' && std::isspace(static_cast<unsigned char>(src[readIndex])))
        {
            readIndex++;
        }
        while (src[readIndex] != '\0')
        {
            if (!std::isspace(static_cast<unsigned char>(src[readIndex])))
            {
                dst[writeIndex] = src[readIndex];
                writeIndex++;
            }
            else
            {
                if (writeIndex > 0 && !std::isspace(static_cast<unsigned char>(dst[writeIndex - 1])))
                {
                    dst[writeIndex] = ' ';
                    writeIndex++;
                }
            }
            readIndex++;
        }
        if (writeIndex > 0 && std::isspace(static_cast<unsigned char>(dst[writeIndex - 1])))
        {
            writeIndex--;
        }
        dst[writeIndex] = '\0';
        return dst;
    }
}
int main()
{
    size_t capacity = 10;
    size_t length = 0;
    char* src = new(std::nothrow) char[capacity];
    if (src == nullptr)
    {
        std::cerr << "Error\n";
        return kilyan::INPUT_ERROR;
    }
    int ch;
    while ((ch = std::cin.get()) != '\n' && ch != EOF)
    {
        if (length + 1 >= capacity)
        {
            size_t newCapacity = capacity * 2;
            char* new_src = new(std::nothrow) char[newCapacity];
            if (new_src == nullptr)
            {
                delete[] src;
                std::cerr << "Error\n";
                return kilyan::INPUT_ERROR;
            }
            for (size_t i = 0; i < length; i++)
            {
                new_src[i] = src[i];
            }
            delete[] src;
            src = new_src;
            capacity = newCapacity;
        }
        src[length] = static_cast<char>(ch);
        length++;
    }
    src[length] = '\0';
    char* dst = new(std::nothrow) char[length + 1];
    if (dst == nullptr)
    {
        delete[] src;
        std::cerr << "Error\n";
        return kilyan::INPUT_ERROR;
    }
    kilyan::removeExtraSpaces(src, dst);
    std::cout << dst << '\n';
    delete[] dst;
    delete[] src;
    return kilyan::SUCCESS;
}