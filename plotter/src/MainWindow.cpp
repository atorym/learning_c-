//
// Created by adm on 22.10.2023.
//

#include <plotter/MainWindow.hpp>

#include <QTimer>

#include <plotter/AboutForm.hpp>
#include <plotter/FuncModel.hpp>

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
  QObject::connect(ui->lw_func, &FuncSelector::selectedFunction, this, &MainWindow::onSelectedFunction);
}


void MainWindow::onSelectedFunction(QVector<FuncFactory::FuncPtr> in) {
  auto func_prev = std::exchange(func_current_, std::move(in));

  if (func_prev == func_current_) {
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

  for (auto const fn : func_current_) {
    auto const graph = ui->qcp_plot->addGraph();
    {
      auto pen_setter = [graph, fn](QVariant color) {
        auto pen = graph->pen();
        assert(color.canConvert<QColor>());
        pen.setColor(std::move(color).value<QColor>());
        graph->setPen(pen);
      };
      pen_setter(FuncModel::instance()->get(fn, FuncModel::Role::color));
      QObject::connect(FuncModel::instance(), &FuncModel::changed, graph, [pen_setter = std::move(pen_setter), fn, plot = ui->qcp_plot](FuncFactory::FuncPtr fnIn, FuncModel::Role role, QVariant value) {
        if (!(role == FuncModel::Role::color && fn == fnIn)) {
          return;
        }
        pen_setter(std::move(value));
        plot->replot();
      });
    }

    std::vector<std::pair<double, double>> data_cache;
    data_cache.reserve(plot_width);

    auto const start = std::chrono::high_resolution_clock::now();

    namespace rv = ranges::views;
    for (auto const x : rv::iota(0, plot_width) | rv::transform([plot_width, rng = ui->qcp_plot->xAxis->range()](auto x) {
           return _::map(x, 0, plot_width, rng.lower, rng.upper);
         })) {
      data_cache.emplace_back(x, fn->ptr(x));
    }

    ui->lw_func->updateElapsed(fn, std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count());

    for (auto const [x, y] : std::move(data_cache)) {
      graph->addData(x, y);
    }
  }

  ui->qcp_plot->replot();
}


void MainWindow::on_pb_center_released() const {
  if (!func_current_.empty()) {
    QCPRange xRng;
    QCPRange yRng;
    for (auto const area : func_current_ | ranges::views::transform([](auto&& i) {
           return i->previewArea;
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


}// namespace lc
