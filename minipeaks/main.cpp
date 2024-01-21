#include <iostream>
#include <vector>

template<typename Iter>
std::vector<typename Iter::value_type> minipeaks(Iter begin, Iter end) {
  ++begin;  // Don't count end values (they only have 1 neighbour)
  if (end - begin <= 1) return {};

  std::vector<typename Iter::value_type> minipeakVals;

  for (auto it = begin; it != end; ++it) {
    const auto& val = *(it - 1);
    if (*(it - 2) + *(it) < 2 * val)
      minipeakVals.emplace_back(val);
  }

  return minipeakVals;
}

template<typename Iter>
void printVec(Iter begin, Iter end) {
  std::cout << '{';
  if (end - begin > 0) {
    for (auto it = begin; it != (end - 1); ++it) {
      std::cout << *it << ", ";
    }
    std::cout << *(end - 1);
  }
  std::cout << '}' << std::endl;
}


int main(int argc, char* argv[]) {
  //const std::vector<size_t> vals { 1, 3, 1, 2, 1 };
  const std::vector<int> vals { 1, 2, 3, 2, 3, 0, -1, 5, 2, -10, -9, -10 };
  printVec(vals.begin(), vals.end());

  const auto returned = minipeaks(vals.begin(), vals.end());
  printVec(returned.begin(), returned.end());

  return 0;
}
