//
// Created by dym on 04.11.23.
//

#include <plotter/GraphMethodModel.hpp>


namespace lc {


GraphMethodModel::~GraphMethodModel() = default;


GraphMethodModel::GraphMethodModel(QObject* parent)
    : QAbstractListModel{parent} {
}


int GraphMethodModel::rowCount(const QModelIndex& parent) const {
  return 0;
}


QVariant GraphMethodModel::data(const QModelIndex& index, int role) const {
  return QVariant();
}


}// namespace lc
