#include <iostream>

size_t numDigits(size_t number) {
  size_t dig = 0;
  while (number != 0) {
    number /= 10;
    dig++;
  }
  return dig;
}

bool palindrome(const size_t in) {
  // Digits can be isolated by integer division by 10

  // First step is to find how many digits
  size_t digits = numDigits(in);
  if (digits <= 1) {  // Edge case
    return false;
  }
 
  bool isPalindrome = true;
  for (size_t d = 0; d < digits/2; ++d) {
    if (getDigit(in, d) != getDigit(in, digits - d)) {
      isPalindrome = false;
    }
  }

  if (isPalindrome) return true;

  // Otherwise, continue on and get descendants.
  size_t descendant = 0;
  size_t newNumDigits = digits/2;
  for (size_t d = 0; d < digits/2; ++d) {
    
  }
}

int main(int argc, char* argv[]) {

  return 0;
}
