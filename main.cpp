/*
Задание №1
 Создайте структуру Student, которая будет хранить имя и баллы студента. Создайте массив студентов
 и используйте функцию std::max_element() для поиска студента с наибольшими баллами, а затем выведите
 на экран имя найденного студента. Функция std::max_element() принимает begin и end списка, и функцию
 с двумя параметрами, которая возвращает true, если первый аргумент меньше второго.

При использовании следующего массива:

    std::array<Student, 8> arr{
        { { "Albert", 3 },
          { "Ben", 5 },
          { "Christine", 2 },
          { "Dan", 8 },                            // Dan имеет больше всего баллов (8)
          { "Enchilada", 4 },
          { "Francis", 1 },
          { "Greg", 3 },
          { "Hagrid", 5 }}
      };

Результатом выполнения вашей программы должно быть следующее:
    Dan is the best student
      */


#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>


    int main() {

  struct student {
    std::string name;
    std::int16_t grade;
  };

  std::array<student, 8> students{
    "Albert", 3,
    "Ben", 5,
    "Christine", 2,
    "Dan", 8,
    "Enchilada", 4,
    "Francis", 1,
    "Greg", 3,
    "Hagrid", 5};

  student *pointer = std::max_element(students.begin(), students.end(),
    [](const student& lhs, const student& rhs) {
      return lhs.grade < rhs.grade;
    });
  std::cout << pointer->name << " is the best student.\n";

  return EXIT_SUCCESS;
}
