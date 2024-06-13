/*
Тест

Задание №1
Для каждой из следующих программ определите результат выполнения. Если программа не скомпилируется, то объясните почему.
Запускать код не нужно, вы должны определить результат/ошибки программ без помощи компилятора.

a)---------------------------------------------------------------------------------------------------------------------
#include <iostream>

class Parent
{
public:
  Parent()
  {
    std::cout << "Parent()\n";
  }
  ~Parent()
  {
    std::cout << "~Parent()\n";
  }
};

class Child: public Parent
{
public:
  Child()
  {
    std::cout << "Child()\n";
  }
  ~Child()
  {
    std::cout << "~Child()\n";
  }
};

int main()
{
  Child ch;
}

Программа скомпилируется. Выведется
parent -> child -> ~child -> ~parent

b)---------------------------------------------------------------------------------------------------------------------
#include <iostream>

class Parent
{
public:
  Parent()
  {
    std::cout << "Parent()\n";
  }
  ~Parent()
  {
    std::cout << "~Parent()\n";
  }
};

class Child: public Parent
{
public:
  Child()
  {
    std::cout << "Child()\n";
  }
  ~Child()
  {
    std::cout << "~Child()\n";
  }
};

int main()
{
  Child ch;
  Parent p;
}

Программа скомпилируется. Выведется
parent -> child -> parent -> ~child -> ~parent -> ~parent

c)---------------------------------------------------------------------------------------------------------------------
#include <iostream>

class Parent
{
private:
  int m_x;
public:
  Parent(int x): m_x(x)
  {
    std::cout << "Parent()\n";
  }
  ~Parent()
  {
    std::cout << "~Parent()\n";
  }

  void print() { std::cout << "Parent: " << m_x << '\n'; }
};

class Child: public Parent
{
public:
  Child(int y): Parent(y)
  {
    std::cout << "Child()\n";
  }
  ~Child()
  {
    std::cout << "~Child()\n";
  }

  void print() { std::cout << "Child: " << m_x << '\n'; }
};

int main()
{
  Child ch(7);
  ch.print();
}

Программа не скомпилируется.
m_x не выведется т.к. у дочернего класса нет к ней доступа.

d)---------------------------------------------------------------------------------------------------------------------
#include <iostream>

class Parent
{
protected:
  int m_x;
public:
  Parent(int x): m_x(x)
  {
    std::cout << "Parent()\n";
  }
  ~Parent()
  {
    std::cout << "~Parent()\n";
  }

  void print() { std::cout << "Parent: " << m_x << '\n'; }
};

class Child: public Parent
{
public:
  Child(int y): Parent(y)
  {
    std::cout << "Child()\n";
  }
  ~Child()
  {
    std::cout << "~Child()\n";
  }

  void print() { std::cout << "Child: " << m_x << '\n'; }
};

int main()
{
  Child ch(7);
  ch.print();
}

Программа скомпилируется. Выведется
parent -> child -> m_x -> ~child -> ~parent
m_x выведется т.к. она является protected членом, но вызывается дочерним классом при наследовании со спецификатором public,
т.е. у дочернего класса есть доступ к переменной.

e)---------------------------------------------------------------------------------------------------------------------
#include <iostream>

class Parent
{
protected:
  int m_x;
public:
  Parent(int x): m_x(x)
  {
    std::cout << "Parent()\n";
  }
  ~Parent()
  {
    std::cout << "~Parent()\n";
  }

  void print() { std::cout << "Parent: " << m_x << '\n'; }
};

class Child: public Parent
{
public:
  Child(int y): Parent(y)
  {
    std::cout << "Child()\n";
  }
  ~Child()
  {
    std::cout << "~Child()\n";
  }
  void print() { std::cout << "Child: " << m_x << '\n'; }
};

class D2 : public Child
{
public:
  D2(int z): Child(z)
  {
    std::cout << "D2()\n";
  }
  ~D2()
  {
    std::cout << "~D2()\n";
  }

  // Обратите внимание, здесь нет метода print()
};

int main()
{
  D2 d(7);
  d.print();
}

Программа скомпилируется.
Хоть в D2 и нет определения print(), компилятор использует одно из родительских определений.

------------------------------------------------------------------------------------------------------------------------

Задание №2

a) Создайте классы Apple и Banana, которые наследуют класс Fruit. У класса Fruit есть две переменные-члены: name и color.

Следующий код:

Приведен в функции main();

Должен выдавать следующий результат:

My apple is red.
My banana is yellow.

b) Добавьте новый класс GrannySmith, который наследует класс Apple.

Следующий код:

Приведен в функции main();

Должен выдавать следующий результат:

   My apple is red.
   My banana is yellow.
   My Granny Smith apple is green.

     */

#include <iostream>
#include <string>

 class Fruit{
protected:
 std::string name_;
 std::string color_;
public:
 Fruit(std::string name, std::string color) : name_{name}, color_{color}{}
 Fruit(){}

 std::string getName(){

   return name_;
 }

 std::string getColor(){

   return color_;
 }
};


class Apple : public Fruit{
public:
 Apple(std::string colour) : Fruit{"apple", colour}{}
 Apple(std::string name, std::string color) : Fruit{name, color}{}

};


class Banana : public Fruit{
public:
 Banana() : Fruit("banana", "yellow"){}
};


class GrannySmith : public Apple{
public:
 GrannySmith() : Apple{"Granny Smith apple", "green"} {}
};

// //задание а
//int main()
//{
//  Apple a("red");
//  Banana b;
//
//  std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
//  std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
//
//  return EXIT_SUCCESS;
//}

//задание б
int main()
{
 Apple a("red");
 Banana b;
 GrannySmith c;

 std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
 std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
 std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

 return EXIT_SUCCESS;
}