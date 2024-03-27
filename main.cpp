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
#include <cstdint>
#include <iostream>
#include <string>


  class Monster {
public:
  enum class MonsterType {
    Dragon = 0,
    Goblin,
    Ogre,
    Orc,
    Skeleton,
    Troll,
    Vampire,
    Zombie,
    MAX_MONSTER_TYPES = 8
  };

private:
  MonsterType m_race = MonsterType::MAX_MONSTER_TYPES;
  std::string m_name = "Default";
  std::size_t m_health = 0;

public:
  Monster() = default;

  Monster(MonsterType race, std::string name, std::size_t health)
      : m_race{race}
      , m_name{name}
      , m_health{health} {
  }

  static std::string getTypeString(MonsterType type) {
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
        return "ERROR";
    }
  }

  void print() {
    std::cout << m_name << " is the " << getTypeString(m_race) << " that has " << m_health << " health points.\n";
  }

  friend class MonsterGenerator;
};


class MonsterGenerator {
private:
  //Массив имен
  constexpr static std::array<std::string, 6> name_array{
    "George",
    "Maxim",
    "Dimanius",
    "Danila",
    "Sergey",
    "Akakiy"};

  //генератор рандомных чисел в заданом диапазоне
  static std::size_t getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // используем static, так как это значение нужно вычислить единожды
    // Равномерно распределяем вычисление значения из нашего диапазона
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
  }

public:
  static Monster generateMonster() {
    Monster a;
    a.m_race = static_cast<Monster::MonsterType>(getRandomNumber(0, static_cast<std::size_t>(Monster::MonsterType::MAX_MONSTER_TYPES) - 1));
    a.m_name = name_array[getRandomNumber(0, 5)];
    a.m_health = getRandomNumber(1, 100);
    return a;
  }
};


int main() {

  srand(static_cast<unsigned int>(time(0)));
  // используем системные часы в качестве стартового значения

  Monster m = MonsterGenerator::generateMonster();
  m.print();

  return 0;
}