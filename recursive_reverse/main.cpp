#include <iostream>
#include <string>
#include <utility>

void reverse(std::string::iterator begin, std::string::iterator end) {
  if (end - begin <= 1) return;

  --end;
  std::swap(*begin, *end);
  return reverse(++begin, end);
}

void reverse_iterative(std::string::iterator begin, std::string::iterator end) {
  for (auto it = begin; end - it > 1; ++it) {
    --end;
    std::swap(*it, *end);
  }
}


int main(int argc, char* argv[]) {
  std::string input;
  std::getline(std::cin, input);

  reverse(input.begin(), input.end());
  std::cout << input << std::endl;
  reverse_iterative(input.begin(), input.end());
  std::cout << input << std::endl;

  return 0;
}
