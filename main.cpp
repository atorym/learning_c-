/*
Задание №1
В итоговом тесте главы №2 мы написали программу имитации мячика, падающего с башни.
Так как тогда мы еще ничего не знали о циклах и не умели их использовать,
то время полета мячика составляло всего лишь 5 секунд.

Измените программу, приведенную ниже, таким образом, чтобы мячик падал ровно то
количество секунд, которое необходимо ему для достижения земли.
 */

#include "constants.h"
#include <cstdint>
#include <iostream>

// Получаем начальную высоту от пользователя и возвращаем её
double getInitialHeight() {
  std::cout << "Enter the initial height of the tower in meters: ";
  double initialHeight;
  std::cin >> initialHeight;
  return initialHeight;
}

// Возвращаем расстояние от земли после "..." секунд падения
double calculateHeight(double initialHeight, int seconds) {
  // Используем формулу: [ s = u * t + (a * t^2) / 2 ], где u(начальная скорость) = 0
  double distanceFallen = (myConstants::gravity * seconds * seconds) / 2;
  double currentHeight = initialHeight - distanceFallen;

  return currentHeight;
}

// Выводим высоту, на которой находится мячик после каждой секунды падения
void printHeight(double height, int seconds) {
  if (height > 0.0) {
    std::cout << "At " << seconds << " seconds, the ball is at height:\t" << height << " meters\n";
  } else
    std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

void calculateAndPrintHeight(double initialHeight, int seconds) {
  double height = calculateHeight(initialHeight, seconds);
  printHeight(height, seconds);
}

double get_current_height(double initialHeight, int seconds) {
  return calculateHeight(initialHeight, seconds);
}

int main() {
  const double initialHeight = getInitialHeight();
  std::int16_t second{0};
  for ( ;get_current_height(initialHeight, second) > 0; ++second) {
    calculateAndPrintHeight(initialHeight, second);
  }
  std::cout << "At " << second << " seconds, the ball is on the ground";
  return 0;
}