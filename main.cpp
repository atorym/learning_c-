#include "constants.h"
#include <iostream>
#include <math.h>
#include <iomanip>


int main() {
#ifdef WIN32
  setlocale(LC_ALL, "Russian");
#endif

  std::wcout << L"\n\n" << L"ПРОГРАММА РАСЧЕТА ЛЕТАЛЬНОСТИ ПАДЕНИЯ" << L"\n";
  double my_vaight;
  std::wcout << L"Введите ваш вес :";
  std::wcin >> my_vaight;
  double floors;
  std::wcout << L"Укажите колличество этажей для расчета: ";
  std::wcin >> floors;
  if (my_vaight < 0 ){
    std::wcout << L"Молодой человек, вы несете какую то чушь" << "\n" << std::endl;
    return EXIT_SUCCESS;
  } else if (floors < 0){
    std::wcout << L"Молодой человек, вы несете какую то чушь" << "\n" << std::endl;
    return EXIT_SUCCESS;
  }
  double h{floors * 3};//определение высоты
  double time(sqrt(2 * h / constants::gravity));
  double V{constants::gravity * time};//определение скорости в момент соприкосновения
  std::wcout << L"При падении с " << floors << L" этажа, вы окажитесь на земле через " << std::setprecision(3) << time << L"с." << L"\n"
             << L" и скорость вашего падения в момент привращения в лепешку будет равнятся " << std::setprecision(4) << V << L"м/c." << L"\n";
if (V<=20.0){
  std::wcout << L"Тем не менее у вас есть шанс остаться в живых." << "\n" << std::endl;
} else {
  std::wcout << L"И ваш шанс на выживание крайне невысок." << "\n" << std::endl;
}
  return EXIT_SUCCESS;
}
