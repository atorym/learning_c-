/*
Задание №4
Настало время для нашего и вашего любимого задания «Blackjack». На этот раз мы перепишем игру «Blackjack»,
которую написали ранее в итоговом тесте главы №6, но уже с использованием классов!
*/

#include <array>
#include <cstdlib>// для rand() и srand()
#include <ctime>  // для time()
#include <iostream>

class Card {
public:
  enum CardSuit {
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,
    MAX_SUITS
  };

  enum CardRank {
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,
    MAX_RANKS
  };

private:
  CardSuit m_suit = MAX_SUITS;
  CardRank m_rank = MAX_RANKS;

public:
  Card() = default;

  Card(CardRank rank, CardSuit suit)
      : m_rank{rank}
      , m_suit{suit} {}

  void printCard() {
    switch (m_rank) {
      case RANK_2:
        std::cout << '2';
        break;
      case RANK_3:
        std::cout << '3';
        break;
      case RANK_4:
        std::cout << '4';
        break;
      case RANK_5:
        std::cout << '5';
        break;
      case RANK_6:
        std::cout << '6';
        break;
      case RANK_7:
        std::cout << '7';
        break;
      case RANK_8:
        std::cout << '8';
        break;
      case RANK_9:
        std::cout << '9';
        break;
      case RANK_10:
        std::cout << 'T';
        break;
      case RANK_JACK:
        std::cout << 'J';
        break;
      case RANK_QUEEN:
        std::cout << 'Q';
        break;
      case RANK_KING:
        std::cout << 'K';
        break;
      case RANK_ACE:
        std::cout << 'A';
        break;
      default:
        std::cout << "ERROR";
        break;
    }
  }

  int getCardValue() {
    switch (m_rank) {
      case RANK_2:
        return 2;
      case RANK_3:
        return 3;
      case RANK_4:
        return 4;
      case RANK_5:
        return 5;
      case RANK_6:
        return 6;
      case RANK_7:
        return 7;
      case RANK_8:
        return 8;
      case RANK_9:
        return 9;
      case RANK_10:
        return 10;
      case RANK_JACK:
        return 10;
      case RANK_QUEEN:
        return 10;
      case RANK_KING:
        return 10;
      case RANK_ACE:
        return 11;
      default:
        return 0;
    }
  }

  friend class Deck;
};


class Deck {
private:
  std::array<Card, 52> m_deck;
  static inline std::size_t m_cardIndex;

public:
  Deck() {
    m_cardIndex = 0;
    int card = 0;
    for (int suit = 0; suit < Card::CardSuit::MAX_SUITS; ++suit)
      for (int rank = 0; rank < Card::CardRank::MAX_RANKS; ++rank) {
        m_deck[card].m_suit = static_cast<Card::CardSuit>(suit);
        m_deck[card].m_rank = static_cast<Card::CardRank>(rank);
        ++card;
      }
  }

  void printDeck() {
    for (auto& card : m_deck) {
      //      printCard(card);
      card.printCard();
      std::cout << ' ';
    }

    std::cout << '\n';
  }

private:
  //// Генерируем случайное число между min и max (включительно).
  //// Предполагается, что srand() уже был вызван
  static int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // используем static, так как это значение нужно вычислить единожды
    // Равномерно распределяем вычисление значения из нашего диапазона
    return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
  }

  static void swapCard(Card& a, Card& b) {
    Card temp = a;
    a = b;
    b = temp;
  }

public:
  void shuffleDeck() {
    //Обнуляем m_cardIndex, т.к. после перетасовки колоды раздается карта, которая является верхней.
    m_cardIndex = 0;
    // Перебираем каждую карту в колоде
    for (int index = 0; index < 52; ++index) {
      // Выбираем любую случайную карту
      int swapIndex = getRandomNumber(0, 51);
      // Меняем местами с нашей текущей картой
      swapCard(m_deck[index], m_deck[swapIndex]);
    }
  }

  Card dealCard() {
    ++m_cardIndex;
    return m_deck[m_cardIndex];
  }
};


char getPlayerChoice() {
  std::cout << "(h) to hit, or (s) to stand: ";
  char choice;
  do {
    std::cin >> choice;
  } while (choice != 'h' && choice != 's');

  return choice;
}


bool playBlackjack(Deck deck) {

  int playerTotal = 0;
  int dealerTotal = 0;

  // Дилер получает одну карту
  dealerTotal += deck.dealCard().getCardValue();
  std::cout << "The dealer is showing: " << dealerTotal << '\n';

  // Игрок получает две карты
  playerTotal += deck.dealCard().getCardValue();
  playerTotal += deck.dealCard().getCardValue();

  // Игрок начинает
  while (true) {
    std::cout << "You have: " << playerTotal << '\n';
    char choice = getPlayerChoice();
    if (choice == 's')
      break;

    playerTotal += deck.dealCard().getCardValue();

    // Смотрим, не проиграл ли игрок
    if (playerTotal > 21)
      return false;
  }

  // Если игрок не проиграл (у него не больше 21 очка), тогда дилер получает карты до тех пор,
  // пока у него в сумме будет не меньше 17 очков
  while (dealerTotal < 17) {
    dealerTotal += deck.dealCard().getCardValue();
    std::cout << "The dealer now has: " << dealerTotal << '\n';
  }

  // Если у дилера больше 21, то он проиграл, а игрок выиграл
  if (dealerTotal > 21)
    return true;

  return (playerTotal > dealerTotal);
}


int main() {
  srand(static_cast<unsigned int>(time(0)));
  // используем системные часы в качестве стартового значения
  rand();
  Deck deck;
  deck.shuffleDeck();

  if (playBlackjack(deck))
    std::cout << "You win!\n";
  else
    std::cout << "You lose!\n";

  return EXIT_SUCCESS;
}