//
// Created by dym on 23.10.23.
//

#include <pswgen/impl.hpp>

#include <random>


namespace pg {
namespace {
namespace _ {


auto random_engine = [] {
  std::random_device rd{};
  return std::mt19937{rd()};
}();


}
}// namespace


void impl(ImplContext const& ctx) {
}


}// namespace pg