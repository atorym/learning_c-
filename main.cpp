#include <cassert>
#include <cstdint>
#include <iostream>

struct natural_ratio {
  std::int16_t numerator;
  std::int16_t denominator;
};


natural_ratio plus(natural_ratio, natural_ratio);
natural_ratio minus(natural_ratio, natural_ratio);
natural_ratio multiply(natural_ratio, natural_ratio);
natural_ratio divide(natural_ratio, natural_ratio);
natural_ratio divide(natural_ratio, natural_ratio);



auto get_user_operation() {
  std::uint16_t selector;
  do {
    std::cout << "Pls enter your type of operation:"
                 "\n0 - exit"
                 "\n1 - + "
                 "\n2 - - "
                 "\n3 - *"
                 "\n4 - /\n";
    std::cin >> selector;
    if (selector == 1) {
      return plus;
    }
    if (selector == 2) {
      return minus;
    }
    if (selector == 3) {
      return multiply;
    }
    if (selector == 4) {
      return divide;
    }
  } while (selector != 0);
  throw std::invalid_argument{"user exit"};
}


natural_ratio get_user_ratio(std::uint8_t number) {
  std::cout << "Enter your " << static_cast<std::uint16_t>(number) << " natural ratio (numerator, denominator): ";
  natural_ratio ratio;
  std::cin >> ratio.numerator >> ratio.denominator;
  return ratio;
}


void print_ratio(natural_ratio v) {
  std::cout << "numerator: " << v.numerator << "\tdenominator: " << v.denominator << '\n';
}


int main() {
  // natural_ratio lhs = get_user_ratio(1);
  // natural_ratio rhs = get_user_ratio(2);
  // auto op = get_user_operation();
  // natural_ratio result = op(lhs, rhs);

  try {
    print_ratio(get_user_operation()(get_user_ratio(1), get_user_ratio(2)));
  } catch(...) {
    std::cout << "user interrupt";
  }

  return EXIT_SUCCESS;
}


natural_ratio plus(natural_ratio lhs, natural_ratio rhs) {
  // TODO realization
  assert(false);
  return {};
}


natural_ratio minus(natural_ratio, natural_ratio) {
  // TODO realization
  assert(false);
  return {};
}


natural_ratio multiply(natural_ratio lhs, natural_ratio rhs) {
  natural_ratio result;
  result.numerator = lhs.numerator * rhs.numerator;
  result.denominator = lhs.denominator * rhs.denominator;
  return result;
}


natural_ratio divide(natural_ratio lhs, natural_ratio rhs) {
  return {lhs.numerator * rhs.denominator, lhs.denominator * rhs.numerator};
}