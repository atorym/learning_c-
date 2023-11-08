//
// Created by dym on 04.11.23.
//

#pragma once

#include <cstdint>

#include <QScrollArea>
#include <QVector>

#include <plotter/FuncFactory.hpp>


class QVBoxLayout;


namespace lc {


class ListFunc final : public QScrollArea {
  Q_OBJECT
public:
  ~ListFunc() override;
  ListFunc(QWidget* parent = nullptr);

  void updateElapsed(lc::FuncFactory::FuncPtr fn, std::size_t us);

signals:
  void selectedFunction(QVector<lc::FuncFactory::FuncPtr>, QPrivateSignal) const;

private slots:
  void onFuncToggled() const;

private:
  QWidget* const     root_;
  QVBoxLayout* const la_;
};


}// namespace lc
