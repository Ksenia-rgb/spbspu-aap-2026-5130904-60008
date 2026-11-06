#include <iostream>
#include <cctype>
#include <cstddef>

namespace kilyan
{
  const int SUCCESS = 0;
  const int MEMORY_ERROR = 1;
  size_t readStream(char*& inputBuffer, size_t& currentCapacity)
  {
    size_t currentLength = 0;
    int inputChar = 0;
    while ((inputChar = std::cin.get()) != '\n' && inputChar != EOF)
    {
      if (currentLength + 1 >= currentCapacity)
      {
        size_t nextCapacity = currentCapacity * 2;
        char* extendedBuffer = new(std::nothrow) char[nextCapacity];
        if (extendedBuffer == nullptr)
        {
          delete[] inputBuffer;
          inputBuffer = nullptr;
          return 0;
        }
        for (size_t i = 0; i < currentLength; ++i)
        {
          extendedBuffer[i] = inputBuffer[i];
        }
        delete[] inputBuffer;
        inputBuffer = extendedBuffer;
        currentCapacity = nextCapacity;
      }
      inputBuffer[currentLength] = static_cast<char>(inputChar);
      currentLength++;
    }
    inputBuffer[currentLength] = '\0';
    return currentLength;
  }
  char* removeExtraSpaces(const char* src, char* dst)
  {
    if (src == nullptr || dst == nullptr)
    {
      return dst;
    }
    const char* reader = src;
    size_t writePos = 0;
    while (*reader != '\0' && std::isspace(static_cast<unsigned char>(*reader)))
    {
      reader++;
    }
    while (*reader != '\0')
    {
      if (!std::isspace(static_cast<unsigned char>(*reader)))
      {
        dst[writePos++] = *reader;
      }
      else
      {
        if (writePos > 0 && !std::isspace(static_cast<unsigned char>(dst[writePos - 1])))
        {
          dst[writePos++] = ' ';
        }
      }
      reader++;
    }
    if (writePos > 0 && std::isspace(static_cast<unsigned char>(dst[writePos - 1])))
    {
      writePos--;
    }
    dst[writePos] = '\0';
    return dst;
  }
}
int main()
{
  size_t initialCapacity = 16;
  char* srcString = new(std::nothrow) char[initialCapacity];
  if (srcString == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return kilyan::MEMORY_ERROR;
  }
  size_t finalLength = kilyan::readStream(srcString, initialCapacity);
  if (srcString == nullptr)
  {
    std::cerr << "Memory allocation failed during reading\n";
    return kilyan::MEMORY_ERROR;
  }
  char* cleanString = new(std::nothrow) char[finalLength + 1];
  if (cleanString == nullptr)
  {
    delete[] srcString;
    std::cerr << "Memory allocation failed for destination\n";
    return kilyan::MEMORY_ERROR;
  }
  kilyan::removeExtraSpaces(srcString, cleanString);
  std::cout << cleanString << '\n';
  delete[] cleanString;
  delete[] srcString;
  return kilyan::SUCCESS;
}
