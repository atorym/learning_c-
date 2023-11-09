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


class FuncModel;


class FuncSelector final : public QScrollArea {
  Q_OBJECT
public:
  ~FuncSelector() override;
  FuncSelector(QWidget* parent = nullptr);

  void updateElapsed(FuncFactory::FuncPtr fn, std::size_t us);

signals:
  void selectedFunction(QVector<FuncFactory::FuncPtr>, QPrivateSignal) const;

private slots:
  void onFuncToggled() const;

private:
  QWidget* const     root_;
  QVBoxLayout* const la_;
};


}// namespace lc
