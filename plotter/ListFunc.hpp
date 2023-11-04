//
// Created by dym on 04.11.23.
//

#pragma once

#include <QListWidget>


class QButtonGroup;


namespace lc {


class ListFunc final : public QListWidget {
  Q_OBJECT
public:
  ~ListFunc() override;
  ListFunc(QWidget* parent = nullptr);

signals:
  void selectedFunction(std::size_t, QPrivateSignal) const;

private:
  QButtonGroup* const rb_group_;
};


}// namespace lc
