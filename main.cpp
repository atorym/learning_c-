/*
Задание №3
Давайте создадим генератор случайных монстров.
a) Сначала создайте перечисление MonsterType со следующими типами монстров: Dragon, Goblin, Ogre, Orc,
Skeleton, Troll, Vampire и Zombie + добавьте MAX_MONSTER_TYPES, чтобы иметь возможность подсчитать
общее количество всех перечислителей.

b) Теперь создайте класс Monster со следующими тремя атрибутами (переменными-членами): тип (MonsterType),
имя (std::string) и количество здоровья (int).

c) Перечисление MonsterType является специфичным для Monster, поэтому переместите его внутрь класса под
спецификатор доступа public.
d) Создайте конструктор, который позволит инициализировать все переменные-члены класса.

Следующий фрагмент кода должен скомпилироваться без ошибок:

int main()
 {
  Monster jack(Monster::Orc, "Jack", 90);

  return 0;
}

e) Теперь нам нужно вывести информацию про нашего монстра. Для этого нужно конвертировать MonsterType в std::string. Добавьте функцию getTypeString(), которая будет выполнять конвертацию, и функцию вывода print().
Следующая программа:

 int main()
 {
  Monster jack(Monster::Orc, "Jack", 90);
  jack.print();

  return 0;
}

Должна выдавать следующий результат:
    Jack is the orc that has 90 health points.
      */
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>


std::minstd_rand0 rand0 = [] {
  std::random_device rd;
  return std::minstd_rand0{rd()};
}();


class Monster {
public:
  enum class MonsterType : std::uint8_t {
    Dragon = 0,
    Goblin,
    Ogre,
    Orc,
    Skeleton,
    Troll,
    Vampire,
    Zombie,
    MAX_MONSTER_TYPES
  };

public:
  Monster() = default;

  Monster(MonsterType race, std::string_view name, std::size_t health)
      : race_{race}
      , name_{name}
      , health_{health} {
  }

  static std::string_view getTypeString(MonsterType type) {
    switch (type) {
      case MonsterType::Dragon:
        return "Dragon";
      case MonsterType::Goblin:
        return "Goblin";
      case MonsterType::Ogre:
        return "Ogre";
      case MonsterType::Orc:
        return "Orc";
      case MonsterType::Skeleton:
        return "Skeleton";
      case MonsterType::Troll:
        return "Troll";
      case MonsterType::Vampire:
        return "Vampire";
      case MonsterType::Zombie:
        return "Zombie";
      default:
        assert(false);
        return "ERROR";
    }
  }


  void print() {
    std::cout << name_ << " is the " << getTypeString(race_) << " that has " << health_ << " health points.\n";
  }

private:
  std::string name_ = "Default";
  std::size_t health_ = 0;
  MonsterType race_ = MonsterType::MAX_MONSTER_TYPES;
};


class MonsterGenerator {
private:
  //Массив имен
  constexpr static std::array<std::string_view, 6> name_array{
    "George",
    "Maxim",
    "Dimanius",
    "Danila",
    "Sergey",
    "Akakiy",
  };

  //генератор рандомных чисел в заданом диапазоне
  static std::size_t getRandomNumber(int min, int max) {
    return std::uniform_int_distribution{min, max}(rand0);
  }

public:
  static Monster generateMonster() {
    return {
      static_cast<Monster::MonsterType>(getRandomNumber(0, static_cast<int>(Monster::MonsterType::MAX_MONSTER_TYPES) - 1)),
      name_array[getRandomNumber(0, name_array.size() - 1)],
      getRandomNumber(1, 100),
    };
  }
};


int main() {
  Monster m = MonsterGenerator::generateMonster();
  m.print();

  return 0;
}
