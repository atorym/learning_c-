//
// Created by adm on 22.10.2023.
//

#include <plotter/MainWindow.hpp>

#include <QTimer>

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


void MainWindow::onSelectedFunction(std::size_t index) {
  if (!std::exchange(func_current_, &FuncFactory::get()[index])) {
    on_pb_center_released();

    for (auto const axis : {ui->qcp_plot->xAxis, ui->qcp_plot->yAxis}) {
      QObject::connect(axis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged), rescale_delay_, qOverload<>(&QTimer::start));
    }
  }

  qcp_replot();
}


void MainWindow::qcp_replot() {
  if (!func_current_) {
    return;
  }

  graph_->data()->clear();
  auto const plot_width = ui->qcp_plot->width();

  auto const start = std::chrono::high_resolution_clock::now();
  namespace rv = ranges::views;
  for (auto const x : rv::iota(0, plot_width) | rv::transform([plot_width, rng = ui->qcp_plot->xAxis->range()](auto x) {
         return _::map(x, 0, plot_width, rng.lower, rng.upper);
       })) {
    graph_->addData(x, func_current_->ptr(x));
  }
  ui->l_elapsed->setText(QString::number(
                           std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count())
                         + "μs");

  ui->qcp_plot->replot();
}


void MainWindow::on_pb_center_released() const {
  for (auto const [axis, rng] : {
         std::pair{ui->qcp_plot->xAxis, func_current_->previewArea.xAxis},
         std::pair{ui->qcp_plot->yAxis, func_current_->previewArea.yAxis},
       }) {
    axis->setRange(rng.min, rng.max);
  }
}


}// namespace lc
