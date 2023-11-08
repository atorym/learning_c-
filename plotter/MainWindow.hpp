//
// Created by adm on 22.10.2023.
//

#pragma once

#include <cstdint>
#include <unordered_map>

#include <QMainWindow>
#include <QPointer>
#include <QScopedPointer>
#include <QVector>

#include <plotter/FuncFactory.hpp>
#include <plotter/ListFunc.hpp>


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
  void onSelectedFunction(QVector<ListFunc::FuncColorPair> index);
  void onColorChanged(FuncFactory::FuncPtr func, QColor color);
  void qcp_replot();

public:
  struct GraphColorPair final {
    QPointer<QCPGraph> grap;
    QColor             color;
  };

  using func_graph_map_t = std::unordered_map<FuncFactory::FuncPtr, GraphColorPair>;

private:
  func_graph_map_t                     func_current_;
  std::vector<QMetaObject::Connection> rescale_delay_axis_conn_;
  QTimer* const                        rescale_delay_;
  QScopedPointer<Ui::MainWindow> const ui;
};


}// namespace lc
