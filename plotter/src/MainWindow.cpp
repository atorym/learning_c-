//
// Created by adm on 22.10.2023.
//

#include <plotter/MainWindow.hpp>

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
    , ui{new Ui::MainWindow}
    , graph_{(ui->setupUi(this), ui->qcp_plot->addGraph())} {
  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);

  ui->qcp_plot->setInteraction(QCP::iRangeDrag, true);
  ui->qcp_plot->setInteraction(QCP::iRangeZoom, true);

  QObject::connect(ui->lw_func, &ListFunc::selectedFunction, this, &MainWindow::onSelectedFunction);
}


void MainWindow::onSelectedFunction(std::size_t index) const {
  graph_->data()->clear();
  auto const func = FuncFactory::get()[index];

  auto const plot_width = ui->qcp_plot->width();
  namespace rv = ranges::views;
  for (auto const x : rv::iota(0, plot_width) | rv::transform([rng = func.previewRange, plot_width](auto x) {
         return _::map(x, 0, plot_width, rng.min, rng.max);
       })) {
    graph_->addData(x, func.ptr(x));
  }

  ui->qcp_plot->rescaleAxes();
  ui->qcp_plot->replot();
}


}// namespace lc
