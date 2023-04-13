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

#include <iostream>
#include <stdint.h>
#include <string>

enum class Monster_type {
  OGRE,
  GOBLIN,
  SKELETON,
  ORK,
  TROLL,
};

struct Monster_parameter {
  Monster_type type;
  std::string name;
  std::int16_t health;
};

std::string get_monster_string_name(Monster_parameter Monster) {
    if (Monster_type::GOBLIN == Monster.type) {
    return "Goblin";
  } else if (Monster_type::OGRE == Monster.type) {
    return "Ogre";
  } else if (Monster_type::ORK == Monster.type) {
    return "Ork";
  } else if (Monster_type::SKELETON == Monster.type) {
    return "Skeleton";
  } else if (Monster_type::TROLL == Monster.type) {
    return "Troll";
  }
  return "monster not defined";
}

void print_monster(Monster_parameter Monster) {

  std::cout << "This " << get_monster_string_name(Monster) << " is called " << Monster.name << " and has " << Monster.health << " health points." << "\n";
}

int main() {

  Monster_parameter Ogre;
  Ogre.type = Monster_type::OGRE;
  Ogre.name = "Boris";
  Ogre.health = 25;
  Monster_parameter Goblin;
  Goblin.type = Monster_type::GOBLIN;
  Goblin.name = "Inokentiy";
  Goblin.health = 10;

  print_monster(Ogre);
  print_monster(Goblin);

  return EXIT_SUCCESS;
}
