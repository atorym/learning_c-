#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>


namespace {
namespace _ {


constexpr std::string_view names[]{
  "Domestos",
  "Artom",
  "Oleg",
  "Obama",
  "Shpachenkof",
};


enum Act : char {
  forward = '1',
  backward,
  forward_repeat,
  backward_repeat,
  i_need_help,
  go_fuck,
};


enum class Errc : std::uint8_t {
  no_error,
  wrong_input,
};


using repeat_accum_t = std::uint16_t;


}// namespace _
}// namespace


void menu() {
  std::cout << "\t\t\tOptions:\n"
            << "\t'" << _::Act::forward << "' insert forward <enter>\n"
            << "\t'" << _::Act::backward << "' paste back <input>\n"
            << "\t'" << _::Act::forward_repeat << "' <n> times insert forward <enter>\n"
            << "\t'" << _::Act::backward_repeat << "' <n> times paste back <enter>\n"
            << "\t'" << _::Act::i_need_help << "' show help\n"
            << "\t'" << _::Act::go_fuck << "' go fuck\n";
}


void help() {
  std::cout << "This program does something:\n";
  menu();
}


void stuff(_::Act const act, std::string_view const input, _::repeat_accum_t const accum) {
  if (accum) {
    switch (act) {
      // показать текущий шаг для многошагового запуска
      case _::Act::forward_repeat:
      case _::Act::backward_repeat:
        std::cout << '[' << accum << "] ";
    }

    auto const sel_name = _::names[std::rand() % std::size(_::names)];
    switch (act) {
      case _::Act::forward:
      case _::Act::forward_repeat:
        std::cout << input << ' ' << sel_name << '\n';
        break;

      case _::Act::backward:
      case _::Act::backward_repeat:
        std::cout << sel_name << ' ' << input << '\n';
        break;

      default:
        assert(false);// в дебажном варианте сборки уронит приложение и остановит дебагер в этом месте
    }
    stuff(act, input, accum - 1);
  }
}


_::Errc stuff(_::Act const act) {
  std::cout << "What do you have there?: " << std::flush;
  std::string       input;
  _::repeat_accum_t accum = 1;

  switch (act) {
    case _::Act::forward_repeat:
    case _::Act::backward_repeat:
      std::cin >> accum;
      // если введенное не соответствует читаемому типу данных
      if (std::cin.fail()) {
        // чищу ввод cin (info https://stackoverflow.com/a/10349885/13161739)
        std::cin.clear();                                                  //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//discard input
        // возвращаю код ошибки
        return _::Errc::wrong_input;
      }

    case _::Act::backward:
    case _::Act::forward:
      std::cin >> input;
      stuff(act, input, accum);
      break;

    default:
      assert(false);
  }
  return _::Errc::no_error;
}


void loop() {
  char act;
  do {
    std::cout << "input: " << std::flush;
    // переставляю cin на конец буфера,
    // на случай если в прошлый раз при чтении было введено что то лишнее (info: https://stackoverflow.com/a/46411174/13161739)
    std::cin.seekg(0, std::ios::end);
    std::cin.clear();
    std::cin >> act;

    switch (act) {
      case _::Act::go_fuck:
        break;

      case _::Act::i_need_help:
        help();
        continue;

      case _::Act::forward:
      case _::Act::backward:
      case _::Act::forward_repeat:
      case _::Act::backward_repeat:
        if (stuff(static_cast<_::Act>(act)) == _::Errc::no_error) {
          continue;
        }

      default:
        std::cout << "Brother, you seem to have mixed something up\n";
    }

  } while (act != _::Act::go_fuck);

  std::cout << "Arividerchi\n";
}


int main(int argc, char* argv[]) {
  std::srand(std::time(nullptr));// rand init

  help();
  loop();

  return EXIT_SUCCESS;
}
