//
// Created by adm on 22.10.2023.
//

#pragma once

#include <cstdint>

#include <QMainWindow>
#include <QScopedPointer>
#include <QVector>

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
  void on_tb_about_released() const;
  void onSelectedFunction(QVector<FuncFactory::FuncPtr> index);
  void qcp_replot();

private:
  QVector<FuncFactory::FuncPtr>        func_current_;
  std::vector<QMetaObject::Connection> rescale_delay_axis_conn_;
  QTimer* const                        rescale_delay_;
  QScopedPointer<Ui::MainWindow> const ui;
};


}// namespace lc
