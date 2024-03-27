/*
Задание №2
Напишите деструктор для следующего класса:
*/

#include <iostream>

class Welcome {
private:
  char* m_data;

public:
  Welcome() {
    m_data = new char[14];
    const char* init = "Hello, World!";
    for (int i = 0; i < 14; ++i)
      m_data[i] = init[i];
  }

  //реализация деструктора
  ~Welcome() {
    delete m_data;
    m_data = nullptr;
  }

  void print() const {
    std::cout << m_data;
  }
};

int main() {
  Welcome hello;
  hello.print();

  return 0;
}