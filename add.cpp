#include <iostream>


int summ(int a, int b) {
	return a + b;
}
int subtraction(int a, int b) {
	return a - b;
}
int derivative(int a, int b) {
	return a * b;
}
int quotient(int a, int b) {
	return a / b;
}
int getInteger() {
	std::cout << "Vvedite vash integer = ";
	int x = 0;
	std::cin >> x;
	return x;
}
void kalkulator(){
	std::cout << "KALKULATOR\n"
            << "Viberite tip operacii (ot 1 do 4) \n 1)+\n 2)-\n 3)* \n 4)/ \n";

  int x = 0;
  std::cin >> x;
  if (x == 1) {
    int a = 0;
    int b = 0;
    std::cout << "Dalee vvedite vashi chisla (celochislennie znachenia)\n";
    a = getInteger();
    b = getInteger();
    std::cout << "rezultat vichisleniy = " << summ(a, b) << "\n KONEC";
  }
  if (x == 2) {
    int a = 0;
    int b = 0;
    std::cout << "Dalee vvedite vashi chisla (celochislennie znachenia)\n";
    a = getInteger();
    b = getInteger();
    std::cout << "rezultat vichisleniy = " << subtraction(a, b) << "\n KONEC";
  }
  if (x == 3) {
    int a = 0;
    int b = 0;
    std::cout << "Dalee vvedite vashi chisla (celochislennie znachenia)\n";
    a = getInteger();
    b = getInteger();
    std::cout << "rezultat vichisleniy = " << derivative(a, b) << "\n KONEC";
  }
  if (x == 4) {
    int a = 0;
    int b = 0;
    std::cout << "Dalee vvedite vashi chisla (celochislennie znachenia)\n";
    a = getInteger();
    b = getInteger();
    std::cout << "rezultat vichisleniy = " << quotient(a, b) << "\n KONEC";
  }
}