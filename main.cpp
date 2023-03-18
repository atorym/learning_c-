#include <iostream>

#include "constants.h"


double path(auto time) {
  return my_constants::gravity * time * time / 2;
}


int main() {
#ifdef WIN32
  setlocale(LC_ALL, "Russian");
#endif
  /*
   Задание 4
   Это уже немного сложнее. Напишите небольшую программу-симулятор падения мячика с башни. Сначала пользователю предлагается ввести
   высоту башни в метрах. Не забывайте о гравитации (9,8м/с2) и о том, что у мячика нет начальной скорости (его держат в руках).
   Программа должна выводить расстояние от земли, на котором находится мячик после 0, 1, 2, 3, 4 и 5 секунд падения. Минимальная высота
   составляет 0 метров (ниже мячику падать нельзя).

   В вашей программе должен быть заголовочный файл constants.h с пространством имен myConstants. В myConstants определите константу для
   хранения значения силы тяжести на Земле (9.8). В качестве напоминания смотрите урок №37.

   Напишите функцию для вычисления высоты мячика через х секунд падения. Используйте следующую формулу:
   высота мячика над землей = константа_гравитации * x_секунд2/2.

   Пример результата выполнения программы:

   Enter the initial height of the tower in meters: 100
   At 0 seconds, the ball is at height: 100 meters
   At 1 seconds, the ball is at height: 95.1 meters
   At 2 seconds, the ball is at height: 80.4 meters
   At 3 seconds, the ball is at height: 55.9 meters
   At 4 seconds, the ball is at height: 21.6 meters
   At 5 seconds, the ball is on the ground.
   */

  std::cout << "Введите высоту башни в метрах: ";
  std::int16_t height;
  std::cin >> height;
  std::int16_t t = 0;
  double height_in_time = height - path(t);
  std::cout << "В момент времени " << t << " с., мячик находится на высоте " << height << " метров.\n";
  ++t;
  while (height_in_time >= 0) {
    height_in_time = height_in_time - path(t);
    if (height_in_time <= 0) {
      std::cout << "В момент времени " << t << " с., мячик находится на земле " << std::endl;
    } else {
      std::cout << "В момент времени " << t << " с., мячик находится на высоте " << height_in_time << " метров.\n";
      ++t;
    }
  }
  return EXIT_SUCCESS;
}