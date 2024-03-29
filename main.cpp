/*
Задание 1.

Какие из следующих переменных могут использоваться лямбдой в функции main() без их явного захвата?

                                                                                                 int i{};                             //да
static int j{};                      //да

int getValue()
{
 return 0;
}

int main()
{
 int a{};                            //нет
 constexpr int b{};                  //да
 static int c{};                     //да
 static constexpr int d{};           //да
 const int e{};                      //да
 const int f{ getValue() };          //да
 static const int g{};               //да
 static const int h{ getValue() };   //да

 [](){
   // Попробуйте использовать переменные без их явного захвата
   a;
   b;
   c;
   d;
   e;
   f;
   g;
   h;
   i;
   j;
 }();

 return 0;
}

Задание 2.
 Что выведет на экран следующая программа? Не запускайте код, а выполните его в уме:
#include <iostream>
#include <string>

 int main()
{
 std::string favoriteFruit{ "grapes" };

 auto printFavoriteFruit{
   [=]() {
     std::cout << "I like " << favoriteFruit << '\n';
   }
 };

 favoriteFruit = "bananas with chocolate";

 printFavoriteFruit();

 return 0;
}

Вывод:
   I like grapes

Задание 3.
   Мы собираемся написать небольшую игру с квадратами чисел.
Суть игры:
 Попросите пользователя ввести 2 числа: первое — стартовое число, которое нужно возвести в квадрат,
   второе — количество чисел, которые нужно возвести в квадрат.  Сгенерируйте случайное целое число от
   2 до 4 и возведите в квадрат указанное пользователем количество чисел, начиная со стартового.
 Умножьте каждое возведенное в квадрат число на сгенерированное ранее число (от 2 до 4).
 Пользователь должен вычислить, какие числа были сгенерированы — он указывает свои предположения.
 Программа проверяет, угадал ли пользователь число, и, если угадал — удаляет угаданное число из списка.
 Если пользователь не угадал число, то игра заканчивается, и программа выводит число, которое было ближе
   всего к окончательному предположению пользователя, но только если последнее предположение не отличалось
   больше чем на 4 единицы от числа из списка.

 Вот первый запуск игры:
Start where?
 4
How many?
 8
I generated 8 square numbers. Do you know what each number is
after multiplying it by 2?
 > 32
Nice! 7 number(s) left.
 > 72
Nice! 6 number(s) left.
 > 50
Nice! 5 number(s) left.
 > 126
126 is wrong! Try 128 next time.

Разбираемся:
 Пользователь решил начать с числа 4 и хочет 8 чисел.
 Квадрат каждого числа будет умножен на 2. Число 2 было выбрано программой случайным образом.
 Программа сгенерировала 8 квадратов чисел, начиная с числа 4: 16 25 36 49 64 81 100 121.
 Но при этом каждое число было умножено на 2, поэтому мы получаем следующие числа: 32 50 72 98 128 162 200 242.
 Теперь пользователь начинает угадывать. Порядок, в котором вводятся догадки, не имеет значения.
 Число 32 значится в списке.
 Число 72 значится в списке.
 Числа 126 нет в списке, поэтому пользователь проиграл. В списке есть число 128, которое отличается не
   более чем на 4 единицы от предположения пользователя, поэтому его мы и выводим в качестве подсказки.

 Вот второй запуск игры:
Start where?
 1
How many?
 3
I generated 3 square numbers. Do you know what each number is
after multiplying it by 4?
 > 4
Nice! 2 numbers left.
 > 16
Nice! 1 numbers left.
 > 36
Nice! You found all numbers, good job!

 Разбираемся:
 Пользователь решил начать с числа 1 и хочет 3 числа.
 Квадрат каждого числа будет умножен на 4.
 Программа сгенерировала следующие числа: 1 4 9.
 Умножаем их на 4: 4 16 36.
 Пользователь выиграл, угадав все числа.

 Вот третий запуск игры:
Start where?
 2
How many?
 2
I generated 2 square numbers. Do you know what each number
is after multiplying it by 4?
 > 21
21 is wrong!

Разбираемся:
 Пользователь решил начать с числа 2 и хочет 2 числа.
 Квадрат каждого числа умножается на 4.
 Программа сгенерировала следующие числа: 16 36.
 Пользователь выдвигает предположение — 21, и проигрывает. 21 не достаточно близко к любому из оставшихся
   чисел, поэтому число-подсказка не выводится.
*/

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>


int main() {

  //диапазон рандомного числа, на которое будут домножаться квадраты чисел
  constexpr std::size_t minimum_random_value = 2;//включительно
  constexpr std::size_t maximum_random_value = 5;//не включительно\

  std::cout << "Where we shell start?\n";
  std::size_t start_value;
  std::cin >> start_value;
  std::cout << "How many numbers generate?\n";
  std::size_t count_of_values;
  std::cin >> count_of_values;

  //заводим рандомный генератор от времени
  srand(time(nullptr));
  //генерируем рандомное число в диапазоне
  std::size_t const random_number = minimum_random_value + rand() % (maximum_random_value - minimum_random_value);


  //заполнение массива чисел
  std::vector<std::size_t> numbers;
  numbers.resize(count_of_values);
  numbers.push_back(start_value);

  for (std::size_t i = 1; i < count_of_values; ++i) {
    numbers.push_back(numbers[i - 1] + 1);
  }
  //заполнение массива домноженых квадратных чисел
  std::vector<std::size_t> sqrt_numbers;
  sqrt_numbers.resize(count_of_values);
  for (std::size_t i = 0; i < count_of_values; ++i) {
    sqrt_numbers.push_back(numbers[i] * numbers[i] * random_number);
  }

  std::cout << "I just genereted " << count_of_values
            << " square numbers. Do you know what each number is after multiplying it by " << random_number << "?\n";

  auto const min_element = std::min_element(sqrt_numbers.cbegin(), sqrt_numbers.cend());
  std::size_t const distance = std::abs(5 - 3);

  //основной loop
  while (true) {
    std::size_t user_value;
    std::cin >> user_value;

    //case true
    if (auto const found = std::find(sqrt_numbers.cbegin(), sqrt_numbers.cend(), user_value); found != sqrt_numbers.cend()) {
      sqrt_numbers.erase(found);
      std::cout << "Great! You've got one! " << sqrt_numbers.size() << " numbers left.\n";
      if (sqrt_numbers.empty()) {
        std::cout << "Yot win! Congratulations!\n";
        break;
      }
    }

    //case wrong but not to much
    else if (*min_element - user_value < distance) {
      std::cout << user_value << " is wrong, try " << *min_element << " next time\n";
      break;
    }

    //case wrong to much
    else {
      std::cout << user_value << " is wrong";
      break;
    }
  }

  return EXIT_SUCCESS;
}