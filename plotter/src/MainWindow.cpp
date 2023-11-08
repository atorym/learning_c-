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
    , ui{new Ui::MainWindow} {

  ui->setupUi(this);

  resizeDocks({ui->dock}, {1}, Qt::Horizontal);

  rescale_delay_->setSingleShot(true);
  rescale_delay_->setInterval(10);

  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);

  ui->qcp_plot->setInteraction(QCP::iRangeDrag, true);
  ui->qcp_plot->setInteraction(QCP::iRangeZoom, true);

  QObject::connect(rescale_delay_, &QTimer::timeout, this, &MainWindow::qcp_replot);
  QObject::connect(ui->lw_func, &ListFunc::selectedFunction, this, &MainWindow::onSelectedFunction);
  QObject::connect(ui->lw_func, &ListFunc::colorChanged, this, &MainWindow::onColorChanged);
}


void MainWindow::onSelectedFunction(QVector<ListFunc::FuncColorPair> in) {
  auto func_prev = std::move(func_current_);
  namespace rv   = ranges::views;
  func_current_  = in | rv::transform([](auto i) -> typename func_graph_map_t::value_type {
    return {i.func, GraphColorPair{.color = i.color}};
  }) | ranges::to<func_graph_map_t>;

  if (ranges::equal(func_prev, in, std::equal_to{}, std::bind_front(&func_graph_map_t::value_type::first), std::bind_front(&ListFunc::FuncColorPair::func))) {
    return;
  }

  if (func_current_.empty()) {
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
  ui->qcp_plot->clearGraphs();
  auto const plot_width = ui->qcp_plot->width();

  for (auto& [impl, painted] : func_current_) {
    painted.grap = ui->qcp_plot->addGraph();
    {
      auto pen = painted.grap->pen();
      pen.setColor(painted.color);
      painted.grap->setPen(pen);
    }

    std::vector<std::pair<double, double>> data_cache;
    data_cache.reserve(plot_width);

    auto const start = std::chrono::high_resolution_clock::now();

    namespace rv = ranges::views;
    for (auto const x : rv::iota(0, plot_width) | rv::transform([plot_width, rng = ui->qcp_plot->xAxis->range()](auto x) {
           return _::map(x, 0, plot_width, rng.lower, rng.upper);
         })) {
      data_cache.emplace_back(x, impl->ptr(x));
    }

    ui->lw_func->updateElapsed(impl, std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count());

    for (auto const [x, y] : std::move(data_cache)) {
      painted.grap->addData(x, y);
    }
  }

  ui->qcp_plot->replot();
}


void MainWindow::on_pb_center_released() const {
  if (!func_current_.empty()) {
    QCPRange xRng;
    QCPRange yRng;
    for (auto const area : func_current_ | ranges::views::transform([](auto&& i) {
           return i.first->previewArea;
         })) {
      for (auto const [axis, rng] : {
             std::pair{&xRng, area.xAxis},
             std::pair{&yRng, area.yAxis.value_or(area.xAxis)},
           }) {
        axis->lower = std::min(axis->lower, rng.min);
        axis->upper = std::max(axis->upper, rng.max);
      }
    }
    ui->qcp_plot->xAxis->setRange(xRng);
    ui->qcp_plot->yAxis->setRange(yRng);
  }
}


void MainWindow::on_tb_about_released() const {
  AboutForm about;
  about.setWindowTitle("About " + windowTitle());
  about.exec();
}


void MainWindow::onColorChanged(FuncFactory::FuncPtr func, QColor color) {
  if (auto const it = func_current_.find(func); it != func_current_.cend()) {
    it->second.grap->setPen(color);
    ui->qcp_plot->replot();
  }
}


}// namespace lc
