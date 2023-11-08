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
  struct FuncColorPair final {
    FuncFactory::FuncPtr func;
    QColor               color;
  };

public:
  ~ListFunc() override;
  ListFunc(QWidget* parent = nullptr);

  void updateElapsed(FuncFactory::FuncPtr fn, std::size_t us);

signals:
  void selectedFunction(QVector<FuncColorPair>, QPrivateSignal) const;
  void colorChanged(FuncFactory::FuncPtr, QColor, QPrivateSignal) const;

private slots:
  void onFuncToggled() const;

private:
  QWidget* const     root_;
  QVBoxLayout* const la_;
};


}// namespace lc

Q_DECLARE_METATYPE(lc::ListFunc::FuncColorPair)
