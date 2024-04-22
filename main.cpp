/*
 Задание №3

Напишите свой собственный класс-массив целых чисел IntArray (не используйте std::array или std::vector).
Пользователи должны передавать размер массива при создании объекта этого класса, а сам массив
(переменная-член) должен выделяться динамически. Используйте стейтменты assert для проверки передаваемых
значений, а также свой конструктор копирования и перегрузку оператора присваивания, если это необходимо,
чтобы следующий код:

 Код приведен в функции IntArray fillArray();
 Код приведен в функции main();

Выдавал следующий результат:

 6 7 3 4 5 8
 6 7 3 4 5 8

*/

#include <cstdint>
#include <iostream>
#include <vector>


class IntArray {
private:
  std::size_t size_ = 1;
  std::int16_t* array_;

public:
  IntArray(std::size_t size)
      : size_{size} {
    if (!size) {
         array_ = nullptr;
        } else {
      array_ = new std::int16_t[size_];
         }
    }

//    деструктор
      ~IntArray() {
        delete[] array_;
        array_ = nullptr;
      }

    std::int16_t& operator[](const std::int16_t iterator) {

      return array_[iterator];
    };

    IntArray& operator=(const IntArray & array);

    friend std::ostream& operator<<(std::ostream& out, const IntArray& array);
  };


  std::ostream& operator<<(std::ostream& out, const IntArray& array) {
    for (int i = 0; i < array.size_; i++) {
      out << array.array_[i] << ' ';
    }

    return out;
  }


  IntArray& IntArray::operator=(const IntArray & array){
    if (this == &array){
      return *this;
    }
    size_ = array.size_;
    for(std::int16_t i = 0; i<size_; i++){
      array_[i] = array.array_[i];
    }

    return *this;
  }


  IntArray fillArray() {
    IntArray a(6);
    a[0] = 6;
    a[1] = 7;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;
    a[5] = 8;

    return a;
  }


  int main() {
    IntArray a = fillArray();
    std::cout << a << '\n';

    IntArray b(1);
    a = a;
    b = a;

    std::cout << b << '\n';

    return EXIT_SUCCESS;
  }