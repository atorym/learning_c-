//
// Created by dym on 24.10.23.
//

#include <pswgen/CapacityBox.hpp>


namespace pg {


CapacityBox::~CapacityBox() = default;


CapacityBox::CapacityBox(QWidget* parent)
    : QGroupBox{parent} {
  setupUi(this);

  for (auto const [sb_e, sb_r, swap] : {
         std::tuple{sb_length_min, sb_length_max, false},
         std::tuple{sb_length_max, sb_length_min, true},
       }) {
    QObject::connect(sb_e, qOverload<int>(&QSpinBox::valueChanged), sb_r, [sb_r = sb_r, swap = swap](int in) {
      if (swap ? (sb_r->value() > in) : (sb_r->value() < in)) {
        sb_r->setValue(in);
      }
    });
  }
}


}// namespace pg
