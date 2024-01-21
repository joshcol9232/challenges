#include <iostream>
#include <string>
#include <utility>

void reverse(std::string::iterator begin, std::string::iterator end) {
  if (--end - begin <= 0) return;

  std::swap(*begin, *end);
  return reverse(++begin, end);
}


int main(int argc, char* argv[]) {
  std::string input;
  std::getline(std::cin, input);

  std::cout << input << std::endl;
  reverse(input.begin(), input.end());
  std::cout << input << std::endl;

  return 0;
}
