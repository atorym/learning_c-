#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <random>


namespace card_spec {


//обьявляем для enum underline type
enum Card_value : std::size_t {
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
  ace
};
enum Suit : std::size_t {
  clubs,
  diamonds,
  hearts,
  spades
};


struct card {
  card_spec::Card_value value;
  card_spec::Suit suit;
};


}// namespace card_spec


namespace constants {


constexpr size_t clubs_begin = 0;
constexpr size_t clubs_end = 12;
constexpr size_t diamonds_begin = 13;
constexpr size_t diamonds_end = 25;
constexpr size_t hearts_begin = 26;
constexpr size_t hearts_end = 38;
constexpr size_t spades_begin = 39;
constexpr size_t spades_end = 51;
constexpr size_t deck_size = 53;


}// namespace constants


void fill_deck(std::array<card_spec::card, constants::deck_size>&, size_t, size_t, card_spec::Suit);
void print_card(card_spec::card const&);
void print_deck(const std::array<card_spec::card, constants::deck_size>&);
void swap_card(card_spec::card&, card_spec::card&);
void shuffle_deck(std::array<card_spec::card, constants::deck_size>&);
std::size_t get_card_value(card_spec::card const&);
bool play_blackjack(const std::array<card_spec::card, constants::deck_size>&);

int main() {
  //создаем массив-карточную колоду
  std::array<card_spec::card, constants::deck_size> deck;
  //делим колоду на 4 части, каждой из которых присваиваем свою масть, после чего инициализируем колоду картами
  fill_deck(deck, constants::clubs_begin, constants::clubs_end, card_spec::clubs);
  fill_deck(deck, constants::diamonds_begin, constants::diamonds_end, card_spec::diamonds);
  fill_deck(deck, constants::hearts_begin, constants::hearts_end, card_spec::hearts);
  fill_deck(deck, constants::spades_begin, constants::spades_end, card_spec::spades);

  std::cout << "The Blackjack!\n\n";
  std::size_t player_enter;
  while (true) {
    std::cout << "Wanna play? (1 - yes, 2 - no)\n";
    std::cin >> player_enter;
    if (player_enter == 1 || player_enter == 2) {

      if (player_enter == 1) {
        shuffle_deck(deck);
        if (play_blackjack(deck) == true) {
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

void fill_deck(std::array<card_spec::card, constants::deck_size>& deck, size_t begin, size_t end, card_spec::Suit suit_type) {
  for (std::size_t i = begin, j = 0; i < end + 1; ++i, ++j) {
    deck[i].suit = suit_type;
    deck[i].value = static_cast<card_spec::Card_value>(j);
  }
}

void print_card(card_spec::card const& card) {
  char value, suit;

  switch (card.value) {
    case card_spec::two:
      value = '2';
      break;
    case card_spec::tree:
      value = '3';
      break;
    case card_spec::fore:
      value = '4';
      break;
    case card_spec::five:
      value = '5';
      break;
    case card_spec::six:
      value = '6';
      break;
    case card_spec::seven:
      value = '7';
      break;
    case card_spec::eight:
      value = '8';
      break;
    case card_spec::nine:
      value = '9';
      break;
    case card_spec::ten:
      value = 'X';
      break;
    case card_spec::jack:
      value = 'J';
      break;
    case card_spec::queen:
      value = 'Q';
      break;
    case card_spec::king:
      value = 'K';
      break;
    case card_spec::ace:
      value = 'A';
      break;
  }

  switch (card.suit) {
    case card_spec::clubs:
      suit = 'C';
      break;
    case card_spec::diamonds:
      suit = 'D';
      break;
    case card_spec::hearts:
      suit = 'H';
      break;
    case card_spec::spades:
      suit = 'S';
      break;
  }
  std::cout << value << ' ' << suit << "   ";
}

void print_deck(const std::array<card_spec::card, 53>& deck) {
  std::for_each(deck.begin(), deck.end(), print_card);
}

void swap_card(card_spec::card& lhs, card_spec::card& rhs) {
  std::swap(lhs.suit, rhs.suit);
  std::swap(lhs.value, rhs.value);
}

void shuffle_deck(std::array<card_spec::card, constants::deck_size>& deck) {
  std::cout << "Shuffling the Deck\n";
  std::random_device rd;
  std::mt19937 mersene(rd());
  std::uniform_int_distribution<> dist(0, 52);
  for (std::size_t i = 0; i <= deck.size(); ++i) {
    swap_card(deck[i], deck[dist(mersene)]);
  }
}

std::size_t get_card_value(card_spec::card const& card) {
  switch (card.value) {
    case card_spec::two:
      return 2;
    case card_spec::tree:
      return 3;
    case card_spec::fore:
      return 4;
    case card_spec::five:
      return 5;
    case card_spec::six:
      return 6;
    case card_spec::seven:
      return 7;
    case card_spec::eight:
      return 8;
    case card_spec::nine:
      return 9;
    case card_spec::ten:
    case card_spec::jack:
    case card_spec::queen:
    case card_spec::king:
      return 10;
    case card_spec::ace:
      return 11;
    default:
      return 0;
  }
}

bool play_blackjack(const std::array<card_spec::card, constants::deck_size>& deck) {
  auto* card_ptr = &deck[1];
  std::size_t dealer_result, player_result, player_enter, amount_of_player_card, amount_of_dealer_card;
  dealer_result = get_card_value(*card_ptr++);
  std::cout << "Dealer got " << dealer_result << " on open card, and 1 close card.\n";
  amount_of_dealer_card = 2;
  dealer_result += get_card_value(*card_ptr++);
  player_result = get_card_value(*card_ptr++) + get_card_value(*card_ptr++);
  amount_of_player_card = 2;
  while (true) {
    std::cout << "You got " << player_result << " on " << amount_of_player_card << " yours card.\nWhat are you gonna do?\n(1 - hit, 2 - stand)\n";
    while (true) {
      std::cin >> player_enter;
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
    return EXIT_SUCCESS;
  }
  // случай, если у игрока меньше 17 и если у игрока меньше чем у дилера
  else {
    return false;
  }
}