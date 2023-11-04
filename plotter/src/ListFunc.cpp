//
// Created by dym on 04.11.23.
//

#include <plotter/ListFunc.hpp>

#include <QRadioButton>

#include <plotter/FuncFactory.hpp>


namespace lc {


ListFunc::~ListFunc() = default;


ListFunc::ListFunc(QWidget* parent)
    : QListWidget{parent} {

  setSelectionMode(NoSelection);

  for (auto const& [i, func] : FuncFactory::get() | ranges::views::enumerate) {
    auto const btn = new QRadioButton{this};
    btn->setText(QLatin1String{func.name.data(), static_cast<int>(func.name.size())});
    QObject::connect(btn, &QAbstractButton::toggled, this, [this, index = i](bool checked) {
      if (checked) {
        emit selectedFunction(index, {});
      }
    });
    setItemWidget(new QListWidgetItem{this}, btn);
  }
}


}// namespace lc
