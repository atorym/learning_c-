/*
Задание №3
 Напишите свою функцию, которая меняет местами значения двух целочисленных переменных.
 Проверку осуществляйте в функции main().
 */

#include <cstdlib>
#include <iostream>


void swap(std::size_t*, std::size_t*);

int main() {

  std::size_t lhs{5};
  std::size_t rhs{10};
  std::size_t *ptr_lhs = &lhs;
  std::size_t *ptr_rhs = &rhs;
  std::cout << "Before swap\nlhs is " << lhs << "\nrhs is " << rhs << '\n';
  swap(ptr_lhs, ptr_rhs);
  std::cout << "After swap\nlhs is " << lhs << "\nrhs is " << rhs << '\n';
  return EXIT_SUCCESS;
}

void swap(std::size_t* lhs, std::size_t* rhs) {
  std::size_t mhs;
  mhs = *lhs;
  *lhs = *rhs;
  *rhs = mhs;
}