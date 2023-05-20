/*
Задание №2
Напишите функцию sumTo(), которая принимает целочисленный параметр с именем value и возвращает сумму всех чисел от 1 до значения value.
Например, если значением value является 5, то sumTo(5) должен возвратить 15, исходя из 1 + 2 + 3 + 4 + 5.
 */


#include <cstdint>
#include <iostream>


std::uint32_t sumTo(std::uint16_t);


int main() {
  std::cout << "Pls enter your int positive value: ";
  std::uint16_t value;
  std::cin >> value;
  std::cout << "Sum of numbers from 1 to " << value << " is: " << sumTo(value);

  return EXIT_SUCCESS;
}


std::uint32_t sumTo(std::uint16_t value) {
  std::uint32_t sum = 1;
  for (std::uint16_t counter = sum + 1; counter <= value; ++counter) {
    sum += counter;
  }
  return sum;
}

/*
Что не так со следующим циклом?

// Выводим все числа от 8 до 0
for (unsigned int count=8; count >= 0; --count)
    cout << count << " ";

Ответ: программа уйдет в бесконечный цикл из за того что используется unsigned int,
 в тот момент, когда count будет =0, и из него вычтется 1, count станет равен своему
 максимальному значению (unsigned int) что то в районе 4000+, после чего будет по
 новой вычитать по 1 за цикл.
cout не std::cout,
fixed size int круче, unsigned int используют обезьяны,

 */