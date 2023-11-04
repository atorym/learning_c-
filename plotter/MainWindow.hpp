//
// Created by adm on 22.10.2023.
//

#pragma once

#include <QMainWindow>
#include <QScopedPointer>

#include <plotter/FuncFactory.hpp>


class QCPGraph;
class QTimer;


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
  void on_pb_center_released() const;
  void onSelectedFunction(std::size_t index);
  void qcp_replot();

private:
  QTimer* const rescale_delay_;
  QScopedPointer<Ui::MainWindow> const ui;
  QCPGraph* const graph_;
  FuncFactory::Func const* func_current_ = nullptr;
};


}// namespace lc
