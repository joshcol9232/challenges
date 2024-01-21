// TOOLS
// =====


// == Prints ==
// - Printing a std::vector

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

