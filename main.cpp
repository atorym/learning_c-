/*
Тест

Реализуем наш пример с Фруктом, о котором мы говорили на уроке №161. Создайте родительский класс Fruit, который
имеет два закрытых члена: name (std::string) и color (std::string). Создайте класс Apple, который наследует свойства
Fruit. У Apple должен быть дополнительный закрытый член: fiber (тип double). Создайте класс Banana, который также
наследует класс Fruit. Banana не имеет дополнительных членов.

Следующий код:

   Код приведен в функции main();

Должен выдавать следующий результат:

   Apple(Red delicious, red, 7.3)
     Banana(Cavendish, yellow)

   */

#include <iostream>
#include <string>


   class Fruit {
private:
 const std::string name_;
 const std::string colour_;

public:
 Fruit(const std::string name, const std::string colour)
     : name_{name}
     , colour_{colour} {}

 std::string get_name() const {

   return name_;
 }

 std::string get_colour() const {

   return colour_;
 }
};

class Apple : Fruit {
private:
 double fiber_;

public:
 Apple(const std::string name, const std::string colour, double fiber)
     : Fruit(name, colour)
     , fiber_{fiber} {}

 double get_fiber() const {

   return fiber_;
 }

 friend std::ostream& operator<<(std::ostream& out, const Apple& fruit);
};

class Banana : Fruit {
public:
 Banana(const std::string name, const std::string colour)
     : Fruit(name, colour) {}

 friend std::ostream& operator<<(std::ostream& out, const Banana& fruit);
};


std::ostream& operator<<(std::ostream& out, const Apple& fruit) {
 out << "Apple (" << fruit.get_name() << ", " << fruit.get_colour() << ", " << fruit.get_fiber() << '\n';

 return out;
}

std::ostream& operator<<(std::ostream& out, const Banana& fruit) {
 out << "Banana (" << fruit.get_name() << ", " << fruit.get_colour() << ")\n";

 return out;
}


int main() {
 const Apple a("Red delicious", "red", 7.3);
 std::cout << a;

 const Banana b("Cavendish", "yellow");
 std::cout << b;

 return 0;
}