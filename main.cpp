/*
Тест
При разработке игры мы решили, что в ней должны быть монстры, потому что всем нравится
сражаться с монстрами. Объявите структуру, которая представляет вашего монстра. Монстр
может быть разным: ogre, goblin, skeleton, orc и troll. Если ваш компилятор поддерживает
C++11, то используйте классы enum, если нет — обычные перечисления.
Каждый монстр также должен иметь имя (используйте std::string) и количество здоровья, которое
отображает, сколько урона он может получить, прежде чем умрет. Напишите функцию printMonster(),
которая выведет все члены структуры. Объявите монстров типа goblin и orc, инициализируйте их,
используя список инициализаторов, и передайте в функцию printMonster().
Пример результата выполнения вашей программы:
 This Goblin is named John and has 170 health.
 This Orc is named James and has 35 health.
*/

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>


enum class monster_type_t : std::uint8_t {
  ogre,
  goblin,
  skeleton,
  ork,
  troll,
};


struct monster_t {
  std::string name;
  std::int16_t health;
  monster_type_t type;
};


std::string get_monster_string_name(monster_type_t type) {
  if (monster_type_t::goblin == type) {
    return "Goblin";
  } else if (monster_type_t::ogre == type) {
    return "Ogre";
  } else if (monster_type_t::ork == type) {
    return "Ork";
  } else if (monster_type_t::skeleton == type) {
    return "Skeleton";
  } else if (monster_type_t::troll == type) {
    return "Troll";
  }
  assert(false);
  return "monster not defined";
}


void print_monster(monster_t monster) {
  std::cout << "This " << get_monster_string_name(monster.type)
            << " is called " << monster.name << " and has " << monster.health << " health points.\n";
}


int main() {
  monster_t Ogre;
  Ogre.type = monster_type_t::ogre;
  Ogre.name = "Boris";
  Ogre.health = 25;
  const monster_t Goblin{
    .name = "Inokentiy",
    .health = 10,
    .type = monster_type_t::goblin};

  print_monster(Ogre);
  print_monster(Goblin);

  return EXIT_SUCCESS;
}
