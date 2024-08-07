/*
 Тест
Исправьте вышеприведенную программу с упрощенной циклической зависимостью, чтобы Item был корректно освобожден.
*/

#include <iostream>
#include <memory>// для std::shared_ptr


class Item {
public:
  std::weak_ptr<Item> m_ptr;// заменил std::shared_ptr на std::weak_ptr

  Item() { std::cout << "Item acquired\n"; }
  ~Item() { std::cout << "Item destroyed\n"; }

};


int main() {
  auto ptr1 = std::make_shared<Item>();

  ptr1->m_ptr = ptr1;// m_ptr теперь является владельцем Item-а, членом которого он является сам
  return 0;
}