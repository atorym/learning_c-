#include <iostream>

/*
void printnumbers(auto a) {
  std::cout << a;
}
*/
int summ(int a, int b) {
  return a + b;
}

int multiply(int a, int b){
  return a * b;
}

float chastnoe(int a, int b){
  return a / b;
}

int doblenomber(int a){
  return a+a;
}

int main() {
  int a;
  int b;
  std::cout << "Vvedite chisla" << std::endl;
  std::cin >> a >> b;
  std::cout << "summa = " << summ(a,b) << std::endl 
  << "proizvedenie 2 summ vashego chisla = " << multiply(summ(a,b), summ(a,b)) << std::endl
  << "chastnoe vashih chisel = " << chastnoe(a,b) << std::endl << "double number pervogo chisla = " << doblenomber(a);
  
  return 0;
}