/*
Тест
Задание №1
Каждая из следующих программ имеет какую-то ошибку. Ваша задача состоит в том, чтобы найти эту ошибку визуально
(не запуская код). Предполагаемый вывод каждой программы: Child
--------------------------------------------------------------------------------------------------------------------------
a) Выведется Parent, т.к. функция getName не virtual и не используется понижающее приведение.

#include <iostream>


class Parent
{
protected:
  int m_value;

public:
  Parent(int value)
      : m_value(value)
  {
  }

  const char* getName() const { return "Parent"; }
};

class Child: public Parent
{
public:
  Child(int value)
      : Parent(value)
  {
  }

  const char* getName() const { return "Child"; }
};


int main()
{
  Child ch(7);
  Parent &p = ch;
  std::cout << p.getName();

  return 0;
}

--------------------------------------------------------------------------------------------------------------------------
b)Нет переопределения функции, т.к. не соответствуют их типы. У child getName константная.

#include <iostream>


 class Parent
 {
protected:
  int m_value;
public:
  Parent(int value)
      : m_value(value)
  {
  }

  virtual const char* getName() { return "Parent"; }
};

class Child: public Parent
{
public:
  Child(int value)
      : Parent(value)
  {
  }

  virtual const char* getName() const { return "Child"; }
};


int main()
{
  Child ch(7);
  Parent &p = ch;
  std::cout << p.getName();

  return 0;
}

--------------------------------------------------------------------------------------------------------------------------
c) Ошибка в функции main(); Неверно выполнена операция присваивания. Ошибка в том что мы записываем в класс parent значение класса child, а не
                                                                                                               изменяем адрес ссылки.

#include <iostream>


                                                                                                             class Parent
{
protected:
  int m_value;

public:
  Parent(int value)
      : m_value(value)
  {
  }

  virtual const char* getName() { return "Parent"; }
};

class Child: public Parent
{
public:
  Child(int value)
      : Parent(value)
  {
  }

  virtual const char* getName() override { return "Child"; }
};


int main()
{
  Child ch(7);
  Parent p = ch;
  std::cout << p.getName();

  return 0;
}

--------------------------------------------------------------------------------------------------------------------------
d)Класс Parent является final. Т.е. его значения не могут быть переопределены.

#include <iostream>


 class Parent final
 {
protected:
  int m_value;

public:
  Parent(int value)
      : m_value(value)
  {
  }

  virtual const char* getName() { return "Parent"; }
};

class Child: public Parent
{
public:
  Child(int value)
      : Parent(value)
  {
  }

  virtual const char* getName() override { return "Child"; }
};


int main()
{
  Child ch(7);
  Parent &p = ch;
  std::cout << p.getName();

  return 0;
}

--------------------------------------------------------------------------------------------------------------------------
e) getName в Child является виртуальной функцией. Т.е. у нее нет определения, есть только прототип.

#include <iostream>


 class Parent
 {
protected:
  int m_value;

public:
  Parent(int value)
      : m_value(value)
  {
  }

  virtual const char* getName() { return "Parent"; }
};

class Child: public Parent
{
public:
  Child(int value)
      : Parent(value)
  {
  }

  virtual const char* getName() = 0;
};

const char* Child::getName()
{
  return "Child";
}


int main()
{
  Child ch(7);
  Parent &p = ch;
  std::cout << p.getName();

  return 0;
}

--------------------------------------------------------------------------------------------------------------------------
f) Ошибка в функции main(); Экземпляру класса child выделяется динамическая память. Указатель класса parent указывает на
  динамическую память экземпляра child. После чего удаляется память, на которую указывает parent. Остается висячий указатель ch.


#include <iostream>


  class Parent
{
protected:
  int m_value;

public:
  Parent(int value)
      : m_value(value)
  {
  }

  virtual const char* getName() { return "Parent"; }
};

class Child: public Parent
{
public:
  Child(int value)
      : Parent(value)
  {
  }

  virtual const char* getName() { return "Child"; }
};


int main()
{
  Child *ch = new Child(7);
  Parent *p = ch;
  std::cout << p->getName();
  delete p;

  return 0;
}

--------------------------------------------------------------------------------------------------------------------------
Задание №2
a) Создайте абстрактный класс Shape. Этот класс должен иметь три метода:
 чистую виртуальную функцию print() с параметром типа std::ostream;
 перегрузку operator<<;
 пустой виртуальный деструктор.
b) Создайте два класса: Triangle и Circle, которые наследуют класс Shape.
 Triangle должен иметь 3 точки в качестве переменных-членов.
 Circle должен иметь одну центральную точку и целочисленный радиус в качестве переменных-членов.
Перегрузите функцию print(), чтобы следующий код:

 Код приведен в функции main(); //задание a:

Выдавал следующий результат:

    Circle(Point(1, 2, 3), radius 7)
      Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9))

        Вот класс Point, который вы можете использовать:

    Приведен ниже class Point{};

 c) Используя код из предыдущих заданий (классы Point, Shape, Circle и Triangle) завершите следующую программу:

 Код приведен в функции main(); //задание с:

 */

#include <iostream>
#include <vector>


   class Point {
 private:
   int m_x = 0;
   int m_y = 0;
   int m_z = 0;

 public:
   Point(int &x, int &y, int &z)
       : m_x(x)
       , m_y(y)
       , m_z(z) {
   }

   friend std::ostream& operator<<(std::ostream& out, const Point& p) {
     out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
     return out;
   }
 };


 class Shape {
 protected:
 public:
   Shape() {}

   virtual ~Shape() {}


   friend std::ostream& operator<<(std::ostream& out, const Shape& s) {
     return s.print(out);
   }

   virtual std::ostream& print(std::ostream& out) const = 0;
 };


 class Triangle : public Shape {
 private:
   Point x_;
   Point y_;
   Point z_;

 public:
   Triangle(Point &x, Point &y, Point &z)
       : x_{x}
       , y_{y}
       , z_{z} {}

   virtual std::ostream& print(std::ostream& out) const override {
     out << "Triangle (" << x_ << ", " << y_ << ", " << z_ << ")";
     return out;
   }
 };


 class Circle : public Shape {
 private:
   Point x_;
   int R_;

 public:
   Circle(Point &x, int &R)
       : x_{x}
       , R_{R} {}

   virtual std::ostream& print(std::ostream& out) const override {
     out << "Circle (" << x_ << ", radius " << R_ << ")";
     return out;
   }

   int get_radius() const {
     return R_;
   }
 };


 ////задание а:
 //int main(){
 //  Circle c(Point(1, 2, 3), 7);
 //  std::cout << c << '\n';
 //
 //  Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
 //  std::cout << t << '\n';
 //
 //  return EXIT_SUCCESS;
 //}

 //задание c:
 int getLargestRadius(std::vector<Shape*>);


 int main() {
   std::vector<Shape*> v;
   v.push_back(new Circle(Point(1, 2, 3), 7));
   v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
   v.push_back(new Circle(Point(4, 5, 6), 3));

   // Вывод элементов вектора v здесь
   for (auto i : v) {
     std::cout << *i << '\n';
   }

   // реализуйте эту функцию
   std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
   // Удаление элементов вектора v здесь
   for (auto i : v) {
     delete i;
   }
   v.clear();

   return EXIT_SUCCESS;
 }


 int getLargestRadius(std::vector<Shape*> v) {
   int largest_radius = 0;
   for (auto i : v) {
     //Использовал static cast вместо dynamic cast, по причине того что dynamic cast не может преобразовать Triangle к Circle
     if (largest_radius < static_cast<Circle*>(i)->get_radius()) {
       largest_radius = static_cast<Circle*>(i)->get_radius();
     }
   }
   return largest_radius;
 }