/*
Задание №1
  Представьте, что вы пишете игру, в которой игрок может иметь 3 типа предметов: зелья здоровья,
  факелы и стрелы. Создайте перечисление с этими типами предметов и фиксированный массив для
  хранения количества каждого типа предметов, которое имеет при себе игрок (используйте стандартные
  фиксированные массивы, а не std::array). У вашего игрока должны быть при себе 3 зелья здоровья,
  6 факелов и 12 стрел. Напишите функцию countTotalItems(), которая возвращает общее количество
  предметов, которые есть у игрока. В функции main() выведите результат работы функции countTotalItems().
*/
#include <cstdlib>
#include <iostream>
#include <cstdint>


namespace Inventory{
enum Inventory{
  POTIONS,
  TORCH,
  ARROWS,
  BAG,
};
}


std::size_t count_total_items(std::size_t count[]);


int main() {
std::size_t count[Inventory::BAG];
count[Inventory::POTIONS] = 3;
count[Inventory::TORCH] = 6;
count[Inventory::ARROWS] = 12;
std::cout << "You have " << count_total_items(count) << " items";
  return EXIT_SUCCESS;
}


std::size_t count_total_items(std::size_t count[]){
  return count[Inventory::POTIONS] + count[Inventory::TORCH] + count[Inventory::ARROWS];
}