//
// Created by dym on 04.11.23.
//

#include <plotter/GraphMethodRadioDelegate.hpp>

#include <QApplication>
#include <QRadioButton>
#include <QStyleOptionButton>


namespace lc {
namespace {
namespace _ {


using Radio = QRadioButton;


}
}// namespace


GraphMethodRadioDelegate::~GraphMethodRadioDelegate() = default;


GraphMethodRadioDelegate::GraphMethodRadioDelegate(QObject* parent)
    : QStyledItemDelegate{parent} {
}


QWidget* GraphMethodRadioDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
  return new _::Radio{parent};
}


void GraphMethodRadioDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
  qobject_cast<_::Radio*>(editor)->setChecked(index.data().toBool());
}


void GraphMethodRadioDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  model->setData(index, qobject_cast<_::Radio*>(editor)->isChecked(), Qt::EditRole);
}


void GraphMethodRadioDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
  QStyleOptionButton styleBtn;
  QRect checkbox_rect = qApp->style()->subElementRect(QStyle::SE_CheckBoxIndicator, &styleBtn);

  //center
  styleBtn.rect = option.rect;
  styleBtn.rect.setLeft(option.rect.x() + option.rect.width() / 2 - checkbox_rect.width() / 2);

  editor->setGeometry(styleBtn.rect);
}


void GraphMethodRadioDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
  //retrieve data
  bool data = index.model()->data(index, Qt::DisplayRole).toBool();

  //create CheckBox style
  QStyleOptionButton styleBtn;
  QRect checkbox_rect = qApp->style()->subElementRect(QStyle::SE_CheckBoxIndicator, &styleBtn);

  //center
  styleBtn.rect = option.rect;
  styleBtn.rect.setLeft(option.rect.x() + option.rect.width() / 2 - checkbox_rect.width() / 2);
  //checked or not checked
  if (data) {
    styleBtn.state = QStyle::State_On | QStyle::State_Enabled;
  } else {
    styleBtn.state = QStyle::State_Off | QStyle::State_Enabled;
  }

  //done! we can draw!
  qApp->style()->drawControl(QStyle::CE_CheckBox, &styleBtn, painter);
}


}// namespace lc
