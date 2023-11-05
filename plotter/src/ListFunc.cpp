//
// Created by dym on 04.11.23.
//

#include <plotter/ListFunc.hpp>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QWidget>

#include <plotter/FuncFactory.hpp>


namespace lc {


ListFunc::~ListFunc() = default;


ListFunc::ListFunc(QWidget* parent)
    : QListWidget{parent}
    , rb_group_{new QButtonGroup{this}} {

  setSelectionMode(NoSelection);

  for (auto const& [i, func] : FuncFactory::get() | ranges::views::enumerate) {
    auto const root = new QWidget{this};

    auto const la = new QHBoxLayout{root};
    la->setContentsMargins(9, 3, 9, 3);

    auto const btn = new QRadioButton{root};
    btn->setText(QString::fromWCharArray(func.name.data(), static_cast<int>(func.name.size())));
    QObject::connect(btn, &QAbstractButton::toggled, this, [this, index = i](bool checked) {
      if (checked) {
        emit selectedFunction(index, {});
      }
    });
    rb_group_->addButton(btn);
    la->addWidget(btn);

    auto const item = new QListWidgetItem{this};
    item->setSizeHint(root->sizeHint());
    setItemWidget(item, root);
  }
}


}// namespace lc
