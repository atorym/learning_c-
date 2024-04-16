/*
Тест

Задание №1
 Предположим, что Square — это класс, а square — это объект этого класса. Какой способ перегрузки лучше использовать
                           для следующих операторов?

 square + square                //перегрузка через дружественную функцию или обычную, если есть get-тер.
 -square                        //перегрузка через member func
 std::cout << square            //перегрузка через дружественную функцию
 square = 7;                    //перегрузка через member func

Задание №2
Напишите класс Average, который будет вычислять среднее значение всех передаваемых ему целых чисел. Используйте два
члена: первый должен быть типа int32_t и использоваться для вычисления суммы всех передаваемых чисел, второй должен
быть типа int8_t и использоваться для вычисления количества передаваемых чисел. Чтобы найти среднее значение, нужно
разделить сумму на количество.

a) Следующий код функции main():

Код приведен в функции main();

Должен выдавать следующий результат:

5 7 11 6 7 7

b) Требуется ли этому классу явный конструктор копирования или оператор присваивания?

Ответ:

*/

#include <cstdint>
#include <iostream>


class Average {
private:
  std::int32_t summ_ = 0;
  std::int16_t amount_ = 0;

public:
  Average(){};

  //конструктор копирования, который не нужен
  //  Average(const Average& copy)
  //      : summ_{copy.summ_}
  //      , amount_{copy.amount_} {};

  // прегрузка оператора присваивания, которая тоже не нужна
  //  Average& operator=(const Average& average) {
  //    summ_ = average.summ_;
  //    amount_ = average.amount_;
  //
  //    return *this;
  //  }

  Average &operator+=(const int rhs);

  friend std::ostream& operator<<(std::ostream& out, const Average& average);
};


Average &Average::operator+=(const int rhs) {
  this->summ_ += rhs;
  this->amount_ += 1;

  return *this;
}


std::ostream& operator<<(std::ostream& out, const Average& average) {
  out << average.summ_ << " / " << average.amount_ << " = " << average.summ_ / average.amount_;

  return out;
}


int main() {

  Average avg;

  avg += 5;
  std::cout << avg << '\n';// 5 / 1 = 5

  avg += 9;
  std::cout << avg << '\n';// (5 + 9) / 2 = 7

  avg += 19;
  std::cout << avg << '\n';// (5 + 9 + 19) / 3 = 11

  avg += -9;
  std::cout << avg << '\n';// (5 + 9 + 19 - 9) / 4 = 6

  (avg += 7) += 11;        // выполнение цепочки операций
  std::cout << avg << '\n';// (5 + 9 + 19 - 9 + 7 + 11) / 6 = 7

  Average copy = avg;
  std::cout << copy << '\n';

  return EXIT_SUCCESS;
}

/*
b) Требуется ли этому классу явный конструктор копирования или оператор присваивания?
 Конструктор копирования классу не нужен. Достаточно использования поверхностного копирования.
 Оператор присваивания классу так же не нужен.
*/