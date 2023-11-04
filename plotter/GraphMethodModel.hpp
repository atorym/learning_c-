//
// Created by dym on 04.11.23.
//

#pragma once

#include <QAbstractListModel>


namespace lc {


class GraphMethodModel final : public QAbstractListModel {
  Q_OBJECT
public:
  ~GraphMethodModel() override;
  GraphMethodModel(QObject* parent = {});

  int rowCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;
};


}// namespace lc
