/*
Задание №1

a) Напишите класс Ball, который должен иметь следующие две закрытые переменные-члены со значениями по умолчанию:
 m_color (Red);
 m_radius (20.0).
 В классе Ball должны быть следующие конструкторы:  для установления значения только для m_color;
 для установления значения только для m_radius;  для установления значений и для m_radius, и для m_color;
 для установления значений, когда значения не предоставлены вообще.
                            Не используйте параметры по умолчанию для конструкторов. Напишите еще одну функцию для вывода цвета (m_color)
и радиуса (m_radius) шара (объекта класса Ball).

b) Теперь обновите ваш код из предыдущего задания с использованием конструкторов с параметрами по умолчанию.
Постарайтесь использовать как можно меньше конструкторов.
*/
#include <iostream>
#include <string>


class Ball {

private:
 std::string m_color = "red";
 double m_radius = 20.0;

public:

 //  Ball(){
 //  }
 //  Ball(std::string color) {
 //    m_color = color;
 //    m_radius = 20.0;
 //  }
 Ball(double radius) {
   m_color = "red";
   m_radius = radius;
 }
 Ball(std::string color = "red", double radius = 20.0) {
   m_color = color;
   m_radius = radius;
 }

 void print() {
   std::cout << "color: " << m_color << ", radius: " << m_radius << '\n';
 }
};


int main() {

 Ball def;
 def.print();

 Ball black("black");
 black.print();

 Ball thirty(30.0);
 thirty.print();

 Ball blackThirty("black", 30.0);
 blackThirty.print();

 return EXIT_SUCCESS;
}

/*
Задание №2

Что произойдет, если не объявить конструктор по умолчанию?

Если не обьявить конструктор по умолчанию, то он создастся неявно.
*/