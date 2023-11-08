//
// Created by adm on 22.10.2023.
//

#include <plotter/MainWindow.hpp>

#include <QTimer>

#include <plotter/AboutForm.hpp>

#include "ui_MainWindow.h"


namespace lc {
namespace {
namespace _ {


auto map(auto x, auto in_min, auto in_max, auto out_min, auto out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


}// namespace _
}// namespace


MainWindow::~MainWindow() = default;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , rescale_delay_{new QTimer{this}}
    , ui{new Ui::MainWindow}
    , graph_{(ui->setupUi(this), ui->qcp_plot->addGraph())} {

  resizeDocks({ui->dock}, {1}, Qt::Horizontal);

  rescale_delay_->setSingleShot(true);
  rescale_delay_->setInterval(100);

  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);

  ui->qcp_plot->setInteraction(QCP::iRangeDrag, true);
  ui->qcp_plot->setInteraction(QCP::iRangeZoom, true);

  QObject::connect(rescale_delay_, &QTimer::timeout, this, &MainWindow::qcp_replot);
  QObject::connect(ui->lw_func, &ListFunc::selectedFunction, this, &MainWindow::onSelectedFunction);
}


void MainWindow::onSelectedFunction(QVector<std::size_t> in) {
  qDebug() << __FUNCTION__ << in;

  auto const func_prev = std::exchange(func_current_index_, in);
  if (func_prev == in) {
    return;
  }

  if (func_current_index_.empty()) {
    rescale_delay_->stop();
    while (!rescale_delay_axis_conn_.empty()) {
      QObject::disconnect(rescale_delay_axis_conn_.back());
      rescale_delay_axis_conn_.pop_back();
    }
  }

  if (func_prev.empty()) {
    on_pb_center_released();

    for (auto const axis : {ui->qcp_plot->xAxis, ui->qcp_plot->yAxis}) {
      rescale_delay_axis_conn_.push_back(
        QObject::connect(axis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged), rescale_delay_, qOverload<>(&QTimer::start)));
    }
  }

  qcp_replot();
}


void MainWindow::qcp_replot() {
  graph_->data()->clear();
  auto const plot_width = ui->qcp_plot->width();

  namespace rv = ranges::views;
  for (auto const [func, index] : func_current_index_ | rv::transform([](auto index) {
         return std::pair{FuncFactory::get()[index].ptr, index};
       })) {
    auto const start = std::chrono::high_resolution_clock::now();
    for (auto const x : rv::iota(0, plot_width) | rv::transform([plot_width, rng = ui->qcp_plot->xAxis->range()](auto x) {
           return _::map(x, 0, plot_width, rng.lower, rng.upper);
         })) {
      graph_->addData(x, func(x));
    }
    ui->lw_func->updateElapsed(index, std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count());
  }

  ui->qcp_plot->replot();
}


void MainWindow::on_pb_center_released() const {
  if (!func_current_index_.empty()) {
    for (auto const [axis, rng] : {
           std::pair{ui->qcp_plot->xAxis, FuncFactory::get()[func_current_index_.front()].previewArea.xAxis},
           std::pair{ui->qcp_plot->yAxis, FuncFactory::get()[func_current_index_.front()].previewArea.yAxis.value_or(FuncFactory::get()[func_current_index_.front()].previewArea.xAxis)},
         }) {
      axis->setRange(rng.min, rng.max);
    }
  }
}


void MainWindow::on_tb_about_released() const {
  AboutForm about;
  about.setWindowTitle("About " + windowTitle());
  about.exec();
}


}// namespace lc
