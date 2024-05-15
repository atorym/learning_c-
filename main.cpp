/*
Тест

Задание №1
 Что бы вы использовали (агрегацию или композицию) для создания следующих объектов? Список создаваемых объектов:

 Красный шар.                             Агрегация
 Работодатель, который нанимает людей.    Агрегация
 Факультет в университете.                Композиция
 Ваш возраст.                             Композиция
 Мешок с шариками.                        Композиция

   Задание №2
   Обновите вышеприведенный пример с Работником/Отделом так, чтобы Отдел мог состоять из нескольких Работников.

 Следующий код:

   Приведен в функции main();

Должен выдавать следующий результат:

   Department: Anton Ivan Max
                  Anton still exists!
                Ivan still exists!
                Max still exists!

                */

#include <cstdint>
#include <iostream>
#include <string>


                class Worker {
private:
 std::string name_;

public:
 Worker(std::string name)
     : name_{name} {}

 std::string get_name() {
   return name_;
 }
};


class Department {
private:
 std::int16_t id_ = 0;
 Worker* worker_[];

public:
 Department(){
   worker_[0] = nullptr;
 }

 void add(Worker* w) {
   if (worker_[id_] != nullptr){
     id_ += 1;
   }
   worker_[id_] = w;


 }

 friend std::ostream& operator<<(std::ostream& out, const Department& department);
};


std::ostream& operator<<(std::ostream& out, const Department& department) {
 out << "Department: ";
 for (std::int8_t i = 0; i <= department.id_; ++i) {
   out << &department.worker_[i] << ',' << ' ';
 }
 out << '\n';

 return out;
}


int main() {
 // Создаем Работников вне области видимости класса Department
 Worker* w1 = new Worker("Anton");
 Worker* w2 = new Worker("Ivan");
 Worker* w3 = new Worker("Max");

 {
   // Создаем Отдел и передаем Работников в качестве параметров конструктора
   Department department;// содаем пустой Отдел
   department.add(w1);
   department.add(w2);
   department.add(w3);

   std::cout << department;

 }// department выходит из области видимости и уничтожается здесь

 std::cout << w1->get_name() << " still exists!\n";
 std::cout << w2->get_name() << " still exists!\n";
 std::cout << w3->get_name() << " still exists!\n";

 delete w1;
 delete w2;
 delete w3;

 return EXIT_SUCCESS;
}