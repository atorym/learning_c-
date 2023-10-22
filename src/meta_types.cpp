//
// Created by dym on 24.10.23.
//

#include <cstdint>
#include <memory>

#include <QMetaType>


namespace {
namespace _ {


using unordered_map_char_size_t = std::unordered_map<char, std::size_t>;


}
}// namespace


Q_DECLARE_METATYPE(std::shared_ptr<_::unordered_map_char_size_t>);
Q_DECLARE_METATYPE(std::shared_ptr<_::unordered_map_char_size_t const>);
