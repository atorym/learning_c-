#include <cmath>
#include <iomanip>
#include <iostream>

#include "constants.h"


int main() {
#ifdef WIN32
  setlocale(LC_ALL, "Russian");
#endif

  std::wcout << L"\n\nПРОГРАММА РАСЧЕТА ЛЕТАЛЬНОСТИ ПАДЕНИЯ\n";
  std::wcout << L"Введите ваш вес: ";
  double my_weight;
  std::wcin >> my_weight;
  std::wcout << L"Укажите количество этажей для расчета: ";
  double floors;
  std::wcin >> floors;
  if (my_weight < 0 || floors < 0) {
    std::wcout << L"Молодой человек, вы несете какую то чушь\n\n";
    return EXIT_SUCCESS;
  }
  const double h        = floors * 3;//определение высоты
  const double time     = std::sqrt(2 * h / constants::gravity);
  const double velocity = constants::gravity * time;//определение скорости в момент соприкосновения
  std::wcout << L"При падении с " << floors << L" этажа, вы окажитесь на земле через " << std::setprecision(3) << time << L"с.\n"
             << L" и скорость вашего падения в момент привращения в лепешку будет равнятся " << std::setprecision(4) << velocity << L"м/c.\n";
  if (velocity <= 20.) {
    std::wcout << L"Тем не менее у вас есть шанс остаться в живых.\n\n";
  } else {
    std::wcout << L"И ваш шанс на выживание крайне невысок.\n\n";
  }
  return EXIT_SUCCESS;
}
