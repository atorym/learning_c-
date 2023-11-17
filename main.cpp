#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <random>
#include <cassert>


std::mt19937& random_engine() {
  static std::mt19937 m_engine = [] {
    std::random_device rd;
    return std::mt19937{rd()};
  }();
  return m_engine;
}


struct card_t {
  //обьявляем для enum underline type
  enum card_value_t : std::uint8_t {
    two,
    tree,
    fore,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
    card_value_count,
  };


  enum suit_t : std::uint8_t {
    diamonds,
    clubs,
    hearts,
    spades,
    suit_count,
  };


  card_value_t value;
  suit_t suit;
};


std::ostream& operator<<(std::ostream& os, const card_t& card) {
  if (card.value < card_t::ten) {
    std::cout << (card.value + 2);
  } else {
    char value;
    switch (card.value) {
      case card_t::ten:
        value = 'X';
        break;
      case card_t::jack:
        value = 'J';
        break;
      case card_t::queen:
        value = 'Q';
        break;
      case card_t::king:
        value = 'K';
        break;
      case card_t::ace:
        value = 'A';
        break;
    }
    std::cout << value << ' ';
  }

  char suit;
  switch (card.suit) {
    case card_t::clubs:
      suit = 'C';
      break;
    case card_t::diamonds:
      suit = 'D';
      break;
    case card_t::hearts:
      suit = 'H';
      break;
    case card_t::spades:
      suit = 'S';
      break;
  }
  std::cout << suit << "   ";
  return os;
}


using card_array_t = std::array<card_t, card_t::card_value_count * card_t::suit_count>;


void fill_deck(card_array_t& deck, card_t::suit_t suit) {
  for (std::size_t i = suit * card_t::card_value_count; i < (suit + 1) * card_t::card_value_count; ++i) {
    deck[i].suit = suit;
    deck[i].value = static_cast<card_t::card_value_t>(i - suit * card_t::card_value_count);
  }
}


void swap_card(card_t& lhs, card_t& rhs) {
  std::swap(lhs.suit, rhs.suit);
  std::swap(lhs.value, rhs.value);
}


void shuffle_deck(card_array_t&);
std::size_t get_card_value(card_t const&);
bool play_blackjack(const card_array_t&);


int main() {
  //создаем массив-карточную колоду
  card_array_t deck;
  //делим колоду на 4 части, каждой из которых присваиваем свою масть, после чего инициализируем колоду картами
  for (std::size_t i{}; i < card_t::suit_count; ++i) {
    fill_deck(deck, static_cast<card_t::suit_t>(i));
  }

  std::cout << "The Blackjack!\n\n";
  std::size_t player_enter;
  while (true) {
    std::cout << "Wanna play? (1 - yes, 2 - no)\n";
    std::cin >> player_enter;
    if (player_enter == 1 || player_enter == 2) {
      if (player_enter == 1) {
        shuffle_deck(deck);
        if (play_blackjack(deck)) {
          std::cout << "You won!\n";
        } else {
          std::cout << "You loose!\n";
        }
      } else {
        break;
      }
    } else {
      std::cout << "Your number isn't correct. Repeat.\n";
    }
  }
  return EXIT_SUCCESS;
}


void print_deck(const card_array_t& deck) {
  for (card_t const& card : deck) {
    std::cout << card;
  }
}


void shuffle_deck(card_array_t& deck) {
  std::cout << "Shuffling the Deck\n";
  std::uniform_int_distribution dist{0, 52};
  for (std::size_t i = 0; i <= deck.size(); ++i) {
    swap_card(deck[i], deck[dist(random_engine())]);
  }
}


std::size_t get_card_value(card_t const& card) {
  if (card.value < card_t::ten) {
    return card.value + 2;
  }
  switch (card.value) {
    case card_t::ten:
    case card_t::jack:
    case card_t::queen:
    case card_t::king:
      return 10;
    case card_t::ace:
      return 11;
    default:
      assert(false);
      return 0;
  }
}


bool play_blackjack(const card_array_t& deck) {
  auto* card_ptr = &deck[0];
  std::size_t dealer_result = get_card_value(*card_ptr++);
  std::cout << "Dealer got " << dealer_result << " on open card, and 1 close card.\n";
  std::size_t amount_of_dealer_card = 2;
  dealer_result += get_card_value(*card_ptr++);
  std::size_t player_result = get_card_value(*card_ptr++) + get_card_value(*card_ptr++);
  std::size_t amount_of_player_card = 2;
  while (true) {
    std::cout << "You got " << player_result << " on " << amount_of_player_card << " yours card.\nWhat are you gonna do?\n(1 - hit, 2 - stand)\n";
    std::size_t player_enter;
    std::cin >> player_enter;
    while (true) {
      if (player_enter == 1 || player_enter == 2) {
        break;
      }
      std::cout << "Your number isn't correct, repeat.\n";
    }
    if (player_enter == 1) {
      player_result += get_card_value(*card_ptr++);
      ++amount_of_player_card;
    }
    if (player_enter == 2) {
      break;
    }
  }


  while (dealer_result <= 17) {
    dealer_result += get_card_value(*card_ptr++);
    ++amount_of_dealer_card;
    std::cout << "Dealer take one more card.\n";
  }
  std::cout << "You got: " << player_result << " Dealer got: " << dealer_result << '\n';
  // случай, если у игрока перебор
  if (player_result > 21) {
    return false;
  }
  // случай, если у дилера перебор
  else if (dealer_result > 21) {
    return true;
  }
  // случай, если у игрока больше чем у дилера.
  else if (player_result > dealer_result) {
    return true;
  }
  // случай, если ничья
  else if (player_result == dealer_result) {
    std::cout << "No one won, results are equal.\n";
    return false;
  }
  // случай, если у игрока меньше 17 и если у игрока меньше чем у дилера
  else {
    return false;
  }
}
