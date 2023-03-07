#include <iostream>


int main() {
#ifdef WIN32
  setlocale(LC_ALL, "Russian");
#endif

  // uniform иницализация
  bool bValue{false};
  // uniform инициализация по умолчанию (присваивается ноль)
  char chValue{};
  // прямая инициализация
  int nValue(5);
  // копирующая инициализация
  float fValue = 12.35;
  // копирующее присваивание или просто присваивание
  double dValue;
  dValue = 10.23;
  // обьявление нескольких переменных в одной строке
  int a, b;
  // инициализация нескольких переменных в одной строке
  int x = 1, y = 3;
  int q(4), e(6);
  int w{2}, h{54};

  return 0;
}