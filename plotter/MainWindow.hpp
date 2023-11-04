//
// Created by adm on 22.10.2023.
//

#pragma once

#include <QMainWindow>
#include <QScopedPointer>

#include <plotter/FuncFactory.hpp>


class QCPGraph;


namespace Ui {
class MainWindow;
}


namespace lc {


class MainWindow final : public QMainWindow {
  Q_OBJECT
public:
  ~MainWindow() override;
  MainWindow(QWidget* parent = nullptr);

private slots:
  void onSelectedFunction(std::size_t index) const;

private:
  QScopedPointer<Ui::MainWindow> const ui;
  QCPGraph* const graph_;
  FuncFactory::Func const* func_current_ = nullptr;
};


}// namespace lc
