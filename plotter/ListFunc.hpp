//
// Created by dym on 04.11.23.
//

#pragma once

#include <cstdint>

#include <QScrollArea>
#include <QVector>


class QVBoxLayout;


namespace lc {


class ListFunc final : public QScrollArea {
  Q_OBJECT
public:
  ~ListFunc() override;
  ListFunc(QWidget* parent = nullptr);

  void updateElapsed(std::size_t index, std::size_t us);

signals:
  void selectedFunction(QVector<std::size_t>, QPrivateSignal) const;

private slots:
  void onFuncToggled() const;

private:
  QWidget* const     root_;
  QVBoxLayout* const la_;
};


}// namespace lc
