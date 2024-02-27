/*
Задание №2
 Используйте std::sort() и лямбду в следующем коде для сортировки времен года по возрастанию средней температуры:

Результатом выполнения вашей программы должно быть следующее:
    Winter Spring Fall Summer
      */


#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

    struct Season
{
  std::string_view name{};
  double averageTemperature{};
};

int main()
{
  std::array<Season, 4> seasons{
    { { "Spring", 285.0 },
      { "Summer", 296.0 },
      { "Fall", 288.0 },
      { "Winter", 263.0 } }
  };

  //Используйте std::sort() здесь
  std::sort(seasons.begin(),seasons.end(),[](const Season lhs, const Season rhs){
    return lhs.averageTemperature<rhs.averageTemperature;
  });

  for (const auto& season : seasons)
  {
    std::cout << season.name << '\n';
  }
  return EXIT_SUCCESS;
}
