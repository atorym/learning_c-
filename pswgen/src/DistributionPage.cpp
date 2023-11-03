//
// Created by dym on 24.10.23.
//

#include <pswgen/DistributionPage.hpp>

#include <sstream>

#include "ui_DistributionPage.h"


namespace pg {
namespace {
namespace _ {


// https://stackoverflow.com/a/69164375/13161739
std::size_t availSize(std::stringstream const& stream) {
  if (stream.rdbuf()) {
    return stream.rdbuf()->pubseekoff(0, std::ios_base::cur, std::ios_base::out);
  } else {
    return 0;
  }
}


}// namespace _
}// namespace


DistributionPage::~DistributionPage() = default;


DistributionPage::DistributionPage(QWidget* parent)
    : QWidget{parent}
    , ui{new Ui::DistributionPage}
    , bars_{(ui->setupUi(this), new QCPBars{ui->plot->xAxis, ui->plot->yAxis})} {
  ui->plot->xAxis->grid()->setVisible(false);
  ui->plot->xAxis->setTickLength(0, 0);
  ui->plot->yAxis->setVisible(false);
}


void DistributionPage::on_pb_run_released() const {
  bars_->data()->clear();

  auto const ss = std::make_shared<std::stringstream>();
  {
    PresetForSamples preset{
      .is = *ss,
    };
    emit initPreset(&preset, {});

    auto const start = std::chrono::high_resolution_clock::now();
    while (_::availSize(*ss) < ui->sb_samples->value()) {
      impl(*preset.ctx);
    }
    ui->l_elapsed->setText(QString::number(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count()) + "ms");
  }

  {
    auto        xTicker = QSharedPointer<QCPAxisTickerText>::create();
    char        xAxisMax{};
    std::size_t yAxisMax{};
    namespace ra = ranges::actions;
    namespace rv = ranges::views;
    for (auto const str = std::move(*ss).str()
           | ra::remove_if(std::bind_front(std::equal_to<>{}, '\n'))
           | ra::sort;
         auto const [i, group] : str
           | rv::chunk_by(std::equal_to<>{})
           | rv::enumerate) {
      ++xAxisMax;
      auto const v = ranges::distance(group);
      bars_->addData(i, v);
      yAxisMax = std::max<std::size_t>(yAxisMax, v);
      xTicker->addTick(i, QString{group.front()});
    }
    ui->plot->xAxis->setRange(-1, xAxisMax);
    ui->plot->yAxis->setRange(0, yAxisMax + 1);
    ui->plot->xAxis->setTicker(std::move(xTicker));
  }

  ui->plot->replot();
}


}// namespace pg
