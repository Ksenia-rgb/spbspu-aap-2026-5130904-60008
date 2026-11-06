#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>

namespace koltsov {
  constexpr int SUCCESS_CODE = 0;
  constexpr int ERR_CODE = 1;
  constexpr std::size_t INIT_BUF = 2;
  constexpr std::size_t INVALID_LEN = static_cast<std::size_t>(-1);

  int loadLine(char *&buf, std::size_t &len, std::size_t &cap);
  int growBuf(char *&buf, std::size_t &cap);
  std::size_t squeezeSpaces(const char *in, char *out);
}

int main()
{
  std::size_t len = 0;
  std::size_t cap = koltsov::INIT_BUF;
  char *line = static_cast<char *>(std::malloc(cap));

  if (line == nullptr) {
    std::cerr << "Memory allocation error\n";
    return koltsov::ERR_CODE;
  }

  if (koltsov::loadLine(line, len, cap) != koltsov::SUCCESS_CODE) {
    std::free(line);
    std::cerr << "Input error\n";
    return koltsov::ERR_CODE;
  }

  char *clean = static_cast<char *>(std::malloc(len + 1));
  if (clean == nullptr) {
    std::free(line);
    std::cerr << "Memory allocation error\n";
    return koltsov::ERR_CODE;
  }

  for (std::size_t i = 0; i <= len; ++i) {
    clean[i] = '\0';
  }

  const std::size_t out_len = koltsov::squeezeSpaces(line, clean);
  if (out_len == koltsov::INVALID_LEN) {
    std::free(clean);
    std::free(line);
    std::cerr << "Transformation error\n";
    return koltsov::ERR_CODE;
  }

  std::cout << clean << '\n';

  std::free(clean);
  std::free(line);

  return koltsov::SUCCESS_CODE;
}

int koltsov::growBuf(char *&buf, std::size_t &cap)
{
  cap *= 2;
  char *const tmp = static_cast<char *>(std::realloc(buf, cap));
  if (tmp == nullptr) {
    return ERR_CODE;
  }
  buf = tmp;
  return SUCCESS_CODE;
}

int koltsov::loadLine(char *&buf, std::size_t &len, std::size_t &cap)
{
  int ch = std::getchar();
  if (ch == EOF) {
    return ERR_CODE;
  }
  while ((ch != '\n') && (ch != EOF)) {
    if ((len + 1) >= cap) {
      if (growBuf(buf, cap) == ERR_CODE) {
        return ERR_CODE;
      }
    }
    buf[len] = static_cast<char>(ch);
    ++len;
    ch = std::getchar();
  }
  buf[len] = '\0';
  return SUCCESS_CODE;
}

std::size_t koltsov::squeezeSpaces(const char *in, char *out)
{
  if ((in == nullptr) || (out == nullptr)) {
    return INVALID_LEN;
  }

  std::size_t pos = 0;
  int had_space = 0;
  int at_start = 1;

  for (std::size_t i = 0; in[i] != '\0'; ++i) {
    const unsigned char c = static_cast<unsigned char>(in[i]);

    if (std::isspace(c)) {
      if ((at_start != 0) || (had_space != 0)) {
        continue;
      }
      had_space = 1;
    } else {
      if (had_space != 0) {
        out[pos] = ' ';
        ++pos;
        had_space = 0;
      }
      out[pos] = in[i];
      ++pos;
      at_start = 0;
    }
  }
  out[pos] = '\0';
  return pos;
}
