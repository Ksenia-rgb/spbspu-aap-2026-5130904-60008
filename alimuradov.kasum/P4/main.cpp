#include <iostream>
#include <cstring>
#include <cctype>

size_t unc_sym(const char* s1, const char* s2, char* out, size_t out_size)
{
  if (s1 == nullptr || s2 == nullptr || out == nullptr || out_size == 0)
  {
    return static_cast<size_t>(-1);
  }

  size_t len = 0;
  unsigned char seen[256] = {0};

  for (const char* p = s1; *p; ++p)
  {
    seen[(unsigned char)*p] |= 1;
  }
  for (const char* p = s2; *p; ++p)
  {
    seen[(unsigned char)*p] |= 2;
  }

  for (int c = 0; c < 256; ++c)
  {
    if (seen[c] == 1 || seen[c] == 2)
    {
      if (len + 1 >= out_size)
      {
        return static_cast<size_t>(-1);
      }
      out[len++] = static_cast<char>(c);
    }
  }
  out[len] = '\0';
  return len;
}

int main()
{
  size_t cap1 = 64, len1 = 0;
  char* first = new (std::nothrow) char[cap1];
  if (!first)
  {
    std::cerr << "failed to allocate memory\n";
    return 1;
  }

  int ch;
  while ((ch = std::cin.get()) != EOF && ch != '\n')
  {
    if (len1 + 1 >= cap1)
    {
      size_t newcap = cap1 * 2;
      char* tmp = new (std::nothrow) char[newcap];
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
    first[len1++] = static_cast<char>(ch);
  }
  first[len1] = '\0';

  size_t cap2 = 64, len2 = 0;
  char* second = new (std::nothrow) char[cap2];
  if (!second)
  {
    delete[] first;
    std::cerr << "failed to allocate memory\n";
    return 1;
  }

  while ((ch = std::cin.get()) != EOF && ch != '\n')
  {
    if (len2 + 1 >= cap2)
    {
      size_t newcap = cap2 * 2;
      char* tmp = new (std::nothrow) char[newcap];
      if (!tmp)
      {
        delete[] first;
        delete[] second;
        std::cerr << "failed to allocate memory\n";
        return 1;
      }
      std::memcpy(tmp, second, len2);
      delete[] second;
      second = tmp;
      cap2 = newcap;
    }
    second[len2++] = static_cast<char>(ch);
  }
  second[len2] = '\0';

  size_t out_cap = len1 + len2 + 1;
  char* result = new (std::nothrow) char[out_cap];
  if (!result)
  {
    delete[] first;
    delete[] second;
    std::cerr << "failed to allocate memory\n";
    return 1;
  }

  if (unc_sym(first, second, result, out_cap) == static_cast<size_t>(-1))
  {
    delete[] first;
    delete[] second;
    delete[] result;
    std::cerr << "result buffer is too small\n";
    return 1;
  }

  std::cout << result << '\n';

  delete[] first;
  delete[] second;
  delete[] result;
  return 0;
}
