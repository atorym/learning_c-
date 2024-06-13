/*
Задание №3
Самое любимое! Будем создавать простую игру, в которой вы будете сражаться с монстрами. Цель игры — собрать максимум золота, прежде чем вы умрете или достигнете 20 уровня.
Игра состоит из трех классов: Creature, Player и Monster. Player и Monster наследуют класс Creature.
a) Сначала создайте класс Creature со следующими членами:
 имя (std::string);
 символ (char);
 количество здоровья (int);
 количество урона, которое он наносит врагу во время атаки (int);
 количество золота, которое он имеет (int).
Создайте полный набор геттеров (по одному на каждую переменную-член класса). Добавьте еще три метода:
 void reduceHealth(int) — уменьшает здоровье Creature на указанное целочисленное значение;  bool isDead() — возвращает true, если здоровье Creature равно 0 или меньше;
 void addGold(int) — добавляет золото Creature-у.

Следующий код:

    Код приведен в main()

      Должен выдавать следующий результат:

    The orc has 3 health and is carrying 15 gold.

      */

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>


  int getRandomNumber(int, int);

class Creature {
protected:
  std::string name_;
  char symbol_;
  int health_;
  int damage_;
  int gold_;

public:
  Creature(std::string name, char simbol, int health, int damage, int gold)
      : name_{name}
      , symbol_{simbol}
      , health_{health}
      , damage_{damage}
      , gold_{gold} {}
  std::string getName() {
    return name_;
  }

  char getSymbol() {
    return symbol_;
  }

  int getHealth() {
    return health_;
  }

  int getDamage() {
    return damage_;
  }

  int getGold() {
    return gold_;
  }

  void reduceHealth(int damage) {
    health_ -= damage;
  }

  bool isDead() {
    if (health_ <= 0) {
      return true;
    } else {
      return false;
    }
  }

  void addGold(int gold) {
    gold_ += gold;
  }
};


class Player : public Creature {
private:
  int level_ = 1;

public:
  Player(std::string name)
      : Creature{name, '@', 10, 1, 0} {}

  void levelUp() {
    level_++;
    damage_++;
  }

  int getLevel() {
    return level_;
  }

  bool hasWon() {
    if (level_ >= 20) {
      return true;
    } else {
      return false;
    }
  }
};


class Monster : public Creature {
private:
  struct MonsterData {
    std::string name;
    char symbol;
    int health;
    int damage;
    int gold;
  };

  static MonsterData monsterData[];


public:
  enum Type {
    DRAGON,
    ORC,
    SLIME,
    MAX_TYPES
  };

  Monster(Type monster)
      : Creature(monsterData[monster].name, monsterData[monster].symbol, monsterData[monster].health,
        monsterData[monster].damage, monsterData[monster].gold) {}

  //диапазон генерации от 0 до MAX_TYPES-1
  static Type getRandomMonster() {
    int temp = getRandomNumber(0, MAX_TYPES - 1);
    switch (temp) {
      case 0:
        return DRAGON;
      case 1:
        return ORC;
      case 2:
        return SLIME;
      default:
        assert(false);
    }
  }
};


Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]{
  {"dragon", 'D', 20, 4, 100},
  {"orc", 'o', 4, 2, 25},
  {"slime", 's', 1, 1, 10}};


int getRandomNumber(int min, int max) {
  static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
  return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


void attackMonster(Monster& m, Player& p) {
  m.reduceHealth(p.getDamage());
  std::cout << "You hit the " << m.getName() << " for " << p.getDamage() << " damage.\n";
}


void attackPlayer(Monster& m, Player& p) {
  p.reduceHealth(m.getDamage());
  std::cout << "The " << m.getName() << " hit you for " << m.getDamage() << " damage.\n";
}


void fightMonster(Monster& m, Player& p) {
  std::cout << "You have encountered " << m.getName() << '\n';

  char user_enter;
  while (true) {
    if (m.getHealth() <= 0 || p.getHealth() <= 0) {
      return;
    }
    std::cout << "(R)un or (F)ight?\n";
    std::cin >> user_enter;


    if (user_enter == 'f' || user_enter == 'F') {
      attackMonster(m, p);
      if (m.getHealth() > 0) {
        attackPlayer(m, p);
      } else {
        std::cout << "You killed " << m.getName() << '\n';
        p.levelUp();
        std::cout << "You are now level " << p.getLevel() << '\n';
        p.addGold(m.getGold());
        std::cout << "You found " << m.getGold() << " gold.\n";
      }
    } else {
      if (getRandomNumber(0, 1) == 1) {
        std::cout << "You successfully fled.\n";
        return;
      } else {
        std::cout << "Your run failed!\n";
        attackPlayer(m, p);
      }
    }
  }
}


int main() {

  //  //задание а
  //  Creature o("orc", 'o', 4, 2, 10);
  //  o.addGold(5);
  //  o.reduceHealth(1);
  //  std::cout << "The " << o.getName() << " has " << o.getHealth() << " health and is carrying " << o.getGold() << " gold." << '\n';

  //  //задание b
  //  std::cout << "Enter your name: ";
  //  std::string temp;
  //  std::cin >> temp;
  //  Player player_1(temp);
  //  std::cout << "Welcome, " << player_1.getName() << '\n'
  //            << "You have " << player_1.getHealth() << " health and are carrying " << player_1.getGold() << " gold.";

  //  //задание d
  //  Monster m(Monster::ORC);
  //  std::cout << "A " << m.getName() << " (" << m.getSimbol() << ") was created.\n";

  //  //задание e
  //  srand(static_cast<unsigned int>(time(0)));
  //  rand();
  //
  //  for (int i = 0; i < 10; ++i) {
  //    Monster m = Monster::getRandomMonster();
  //    std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
  //  }

  //задание f
  srand(static_cast<unsigned int>(time(0)));
  rand();

  std::cout << "Enter your name: ";
  std::string temp;
  std::cin >> temp;
  Player player_1(temp);
  std::cout << "Welcome, " << player_1.getName() << ".\n";

  while (true) {
    Monster monster_1 = Monster::getRandomMonster();
    fightMonster(monster_1, player_1);

    if (player_1.hasWon()) {
      std::cout << "Your rich 20 level. You has won!\nYou has collect " << player_1.getGold()
                << " gold to spend. Congratulations!";
      break;
    }

    if (player_1.isDead()) {
      std::cout << "You are died at level " << player_1.getLevel() << " and with " << player_1.getGold()
                << " gold.\nToo bad you can't take it with you!";
      break;
    }
  }

  return EXIT_SUCCESS;
}