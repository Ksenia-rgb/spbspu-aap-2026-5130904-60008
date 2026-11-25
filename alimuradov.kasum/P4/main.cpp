#include <iostream>
#include <cstring>
#include <cctype>

namespace alimuradov
{
  constexpr size_t kCharCount = 256;
  constexpr size_t kInitialCapacity = 64;

  size_t uncSym(const char* s1, const char* s2, char* out, size_t out_size)
  {
    if (s1 == nullptr || s2 == nullptr || out == nullptr || out_size == 0)
    {
      return static_cast< size_t >(-1);
    }

    size_t len = 0;
    unsigned char seen[kCharCount] = {0};

    for (const char* p = s1; *p; ++p)
    {
      seen[static_cast< unsigned char >(*p)] |= 1;
    }
    for (const char* p = s2; *p; ++p)
    {
      seen[static_cast< unsigned char >(*p)] |= 2;
    }

    for (size_t c = 0; c < kCharCount; ++c)
    {
      if (seen[c] == 1 || seen[c] == 2)
      {
        if (len + 1 >= out_size)
        {
          return static_cast< size_t >(-1);
        }
        out[len++] = static_cast< char >(c);
      }
    }
    out[len] = '\0';
    return len;
  }
}

int main()
{
  const char* const second = "abc_ef";

  size_t cap1 = alimuradov::kInitialCapacity;
  size_t len1 = 0;
  char* first = new (std::nothrow) char[cap1];
  if (!first)
  {
    std::cerr << "failed to allocate memory\n";
    return 1;
  }

  int ch = 0;
  int got_newline = 0;

  while ((ch = std::cin.get()) != EOF && ch != '\n')
  {
    if (std::iscntrl(static_cast< unsigned char >(ch)) == 0)
    {
      if (len1 + 1 >= cap1)
      {
        const size_t newcap = cap1 * 2;
        char* const tmp = new (std::nothrow) char[newcap];
        if (!tmp)
        {
          delete[] first;
          std::cerr << "failed to allocate memory\n";
          return 1;
        }
        std::memcpy(tmp, first, len1);
        delete[] first;
        first = tmp;
        cap1 = newcap;
      }
      first[len1++] = static_cast< char >(ch);
    }
  }

  if (ch == '\n')
  {
    got_newline = 1;
  }

  if (got_newline == 0 && len1 == 0)
  {
    delete[] first;
    std::cerr << "empty input\n";
    return 1;
  }

  first[len1] = '\0';

  const size_t out_cap = len1 + std::strlen(second) + 1;
  char* const result = new (std::nothrow) char[out_cap];
  if (!result)
  {
    delete[] first;
    std::cerr << "failed to allocate memory\n";
    return 1;
  }

  if (alimuradov::uncSym(first, second, result, out_cap) == static_cast< size_t >(-1))
  {
    delete[] first;
    delete[] result;
    std::cerr << "result buffer is too small\n";
    return 1;
  }

  std::cout << result << '\n';

  delete[] first;
  delete[] result;
  return 0;
}
