/*
Задание №1
Добавьте в следующую программу инициализацию нестатических членов и список инициализации членов:
*/


#include <cstdint>
#include <iostream>


class Thing {
private:
  std::string m_color{"blue"};
  double m_radius{20.0};

public:
  // Конструктор по умолчанию без параметров
  Thing() {
  }

  // Конструктор с параметром color (для radius предоставлено значение по умолчанию)
  Thing(const std::string& color) : m_color(color) {

  }

  // Конструктор с параметром radius (для color предоставлено значение по умолчанию)
  Thing(double radius) : m_color("blue"){
    m_color = "blue";
    m_radius = radius;
  }

  // Конструктор с параметрами color и radius
  Thing(const std::string& color, double radius) : m_color(color), m_radius(radius) {

  }

  void print() {
    std::cout << "color: " << m_color << " and radius: " << m_radius << '\n';
  }
};


int main() {

  Thing defl;
  defl.print();

  Thing red("red");
  red.print();

  Thing thirty(30.0);
  thirty.print();

  Thing redThirty("red", 30.0);
  redThirty.print();

  return EXIT_SUCCESS;
}

/*
 Задание №2
Зачем мы объявили пустой конструктор по умолчанию в программе из задания №1? Все же переменные-члены
и так имеют значения по умолчанию.
 
Пустой конструктор был обьявлен по причине его вызова в main. При существовании других конструкторов,
значения по умолчанию игнорируются компилятором, т.е. вызвать класс без параметров невозможно.
*/