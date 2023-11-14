/*
Задание №2
 Создайте структуру, содержащую имя и оценку учащегося (по шкале от 0 до 100). Спросите у пользователя,
 сколько учеников он хочет ввести. Динамически выделите массив для хранения всех студентов. Затем
 попросите пользователя ввести для каждого студента его имя и оценку. Как только пользователь ввел
 все имена и оценки, отсортируйте список оценок студентов по убыванию (сначала самый высокий бал).
 Затем выведите все имена и оценки в отсортированном виде.
*/
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>


std::size_t read_clamp(std::size_t floor = 1, std::size_t top = 100) {
  std::size_t out;
  while (true) {
    std::cin >> out;
    if (out == std::clamp(out, floor, top)) {
      break;
    }
    std::cout << "Your input isn't correct, repeat\n: ";
  }
  return out;
}


int main() {
  //создаем структуру с оценкой и именем студента
  struct Student {
    std::string name;
    std::size_t grade;
  };
  std::cout << "How many students do you have? (1-100)\n: ";
  const std::size_t amount_of_students = read_clamp();
  //создаем массив структур (vector не работает)
  //  std::vector<Student> student;
  Student* student = new Student[amount_of_students];
  //заменить 32767 на что то типа std::cin.end (оператор конца стэка std::sin), да и getline не рабоатет

  for (std::size_t i = 0; i < amount_of_students; ++i) {
    std::cout << "Pls enter name of your " << i + 1 << " student\n:";
    //getline - не рабоает
    //    std::getline(std::cin, student[i].name);
    std::cin >> student[i].name;
    std::cout << "Pls enter grade of your " << i + 1 << " student\n:";
    //ввод с проверкой на идиота
    student[i].grade = read_clamp();
  }
  //сортируем массив
  for (std::size_t i = 0; i < amount_of_students - 1; ++i) {
    for (std::size_t j = i; j < amount_of_students - 1; ++j) {
      if (student[j].grade < student[j + 1].grade)
        std::swap(student[j], student[j + 1]);
    }
  }
  //выводим сортированный массив на экран
  std::cout << "There is your sorted by grade list of students:\n";
  for (std::size_t i = 0; i < amount_of_students; ++i) {
    std::cout << student[i].grade << ' ' << student[i].name << '\n';
  }

  delete[] student;

  return EXIT_SUCCESS;
}
