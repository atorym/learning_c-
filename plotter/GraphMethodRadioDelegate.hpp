//
// Created by dym on 04.11.23.
//

#pragma once

#include <QStyledItemDelegate>


namespace lc {


// https://github.com/pierreet/BooleanCheckBoxDelegate/blob/master/BooleanCheckBoxDelegate.h
class GraphMethodRadioDelegate final : public QStyledItemDelegate {
  Q_OBJECT
public:
  ~GraphMethodRadioDelegate() override;
  GraphMethodRadioDelegate(QObject* parent = {});

  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
  void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
  void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};


}// namespace lc