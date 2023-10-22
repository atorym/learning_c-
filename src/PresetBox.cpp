//
// Created by dym on 23.10.23.
//

#include <PresetBox.hpp>


namespace pg {


PresetBox::~PresetBox() = default;


PresetBox::PresetBox(QWidget* parent)
    : QGroupBox{parent} {
  setupUi(this);

  auto const bnt_list = findChildren<QRadioButton*>();
  // настройки эксклюзивности
  for (auto const i : bnt_list) {
    // запретить выключать всё одновременно
    QObject::connect(i, &QAbstractButton::toggled, this, [btn = i, bnt_list](bool f) {
      auto const count = ranges::fold_left(bnt_list, std::size_t{}, [](auto counter, QAbstractButton* btn) {
        return counter + (btn->isChecked() ? 1 : 0);
      });
      if (!f && count == 0) {
        btn->setChecked(true);
      }
    });
  }

  QObject::connect(rb_manual, &QAbstractButton::toggled, this, [this] {
    le_manual->setEnabled(rb_manual->isChecked());
  });

  for (auto const i : bnt_list) {
    QObject::connect(i, &QAbstractButton::released, this, [this, btn = i, is = i->isChecked()]() mutable {
      // защита от эмита при тыкании на одну и ту же кнопку
      bool const is_in = btn->isChecked();
      if (std::exchange(is, is_in) != is_in) {
        emit some_changed({});
      }
    });
  }
  QObject::connect(le_manual, &QLineEdit::textChanged, this, std::bind_front(&PresetBox::some_changed, this, QPrivateSignal{}));
}


}// namespace pg
