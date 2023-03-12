#include <iostream>


int main() {
#ifdef WIN32
  setlocale(LC_ALL, "Russian");
#endif

  std::wcout << L"Программа по определению ASCII кода по литере.\n\n"
             << L"Введите желаемую литеру или сочетание символов\n"
             << L"(для завершения программы введите символ <+>) :\n";
  char ch;
  int i{0};
  while (i < 100) {
    std::cin >> ch;
    if (ch == '+') {
      i = 100;
    } else {
      std::wcout << L"Ваша литера <" << ch
                 << L"> имеет следующий \n ASCII код "
                 << static_cast<int>(ch) << "." << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
