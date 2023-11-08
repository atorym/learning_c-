//
// Created by dym on 04.11.23.
//

#pragma once

#include <QScrollArea>


class QVBoxLayout;


namespace lc {


class ListFunc final : public QScrollArea {
  Q_OBJECT
public:
  ~ListFunc() override;
  ListFunc(QWidget* parent = nullptr);

signals:
  void selectedFunction(std::size_t, QPrivateSignal) const;

public slots:
  void updateElapsed(std::size_t index);

private:
  QWidget* const     root_;
  QVBoxLayout* const la_;
};


}// namespace lc
