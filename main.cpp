/*
Тест
Напишите класс, переменной-членом которого является строка. Перегрузите оператор () для возврата подстроки,
которая начинается с индекса, указанного в значении первого параметра. Второй параметр должен указывать
требуемую длину подстроки. Подсказки:  Вы можете использовать индекс массива [] для доступа к отдельным
символам строки.  Вы можете использовать оператор += для добавления чего-либо к строке.

Следующий фрагмент кода:

   Код приведен в main

     Должен выдавать следующий результат:

   world!

   */


#include <iostream>
#include <string>


class Mystring {
private:
  std::string my_string_;

public:
  Mystring(const std::string_view string)
      : my_string_{string} {};

  std::string operator()(int where_start, int amount) {
    std::string temp;
    for (auto i = 0; i <= amount; ++i) {
      temp.push_back(my_string_[where_start]);
      where_start += 1;
    }

    return temp;
  }
};


int main() {

  Mystring string("Hello, world!");
  std::cout << string(7, 6);// начинаем с 7 символа (индекса) и возвращаем следующие 6 символов

  return EXIT_SUCCESS;
}