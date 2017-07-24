#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);
  std::vector<char> txt((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
  file.close();

  const std::string allowed = "><+-.,[]";

  txt.erase(std::remove_if(txt.begin(), txt.end(), [&](char c) {
    return allowed.find(c) == std::string::npos;
  }), txt.end());

  char m[30000];
  int i = 0;

  int j = 0;
  const int n = txt.size();

  while (j < n) {
    char c = txt[j];
    switch (c) {
    case '>':
      ++i;
      break;
    case '<':
      --i;
      break;
    case '+':
      ++m[i];
      break;
    case '-':
      --m[i];
      break;
    case '.':
      std::cout << m[i];
      break;
    case ',':
      std::cin >> m[i];
      break;
    case '[':
      if (m[i] == 0) {
        int b = 1;
        while (b != 0) {
          ++j;
          if (txt[j] == '[') {
            ++b;
          } else if (txt[j] == ']') {
            --b;
          }
        }
      }
      break;
    case ']':
      if (m[i] != 0) {
        int b = 1;
        while (b != 0) {
          --j;
          if (txt[j] == ']') {
            ++b;
          } else if (txt[j] == '[') {
            --b;
          }
        }
        --j;
      }
      break;
    default:
      std::cerr << "error: unexpected character " << c << std::endl;
      return EXIT_FAILURE;
    }
    ++j;
  }

  return 0;
}
