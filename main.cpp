#include <iostream>
#include <limits>
#include <stdexcept>

unsigned safe_multiply(unsigned a, unsigned b) {
  using lim_int = std::numeric_limits<unsigned>;
  const unsigned maxUnsigned = lim_int::max();
  if (a > 0 && b > 0 && a > maxUnsigned / b)
    throw std::overflow_error("multiply");
  return a * b;
}

unsigned safe_add(unsigned a, unsigned b) {
  using lim_int = std::numeric_limits<unsigned>;
  const unsigned maxUnsigned = lim_int::max();
  if (a > maxUnsigned - b)
    throw std::overflow_error("add");
  return a + b;
}

bool isPyth(unsigned a, unsigned b, unsigned c) {
  bool p = (safe_multiply(a, a) ==
            safe_add(safe_multiply(b, b), safe_multiply(c, c)));
  p = p || (safe_multiply(b, b) ==
            safe_add(safe_multiply(a, a), safe_multiply(c, c)));
  p = p || (safe_multiply(c, c) ==
            safe_add(safe_multiply(a, a), safe_multiply(b, b)));
  return p;
}

int main() {
  using u_t = unsigned;

  u_t a = 0, b = 0, c = 0;
  std::cin >> c >> b;

  size_t count = 0;

  try {
    while (std::cin >> a) {
      count += isPyth(a, b, c) ? 1 : 0;
      c = b;
      b = a;
    }
  } catch (const std::overflow_error &e) {
    std::cerr << "Overflow: " << e.what() << "\n";
    return 2;
  }

  if (std::cin.eof()) {
    std::cout << count;
    std::cout << "\n";
  } else if (std::cin.fail()) {
    std::cerr << "Error input reading\n";
    return 1;
  }
}
