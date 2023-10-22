//
// Created by dym on 24.10.23.
//

#include <DistributionPage.hpp>


namespace pg {


DistributionPage::~DistributionPage() = default;


DistributionPage::DistributionPage(QWidget* parent)
    : QWidget{parent}
    , bars_{(setupUi(this), new QCPBars{plot->xAxis, plot->yAxis})} {
}


void DistributionPage::updateDistribution(std::shared_ptr<const std::unordered_map<char, std::size_t>> map) {
  namespace rv = ranges::views;
  bars_->setData(
    rv::iota(0u, map->size()) | ranges::to<QVector<double>>,
    *map | rv::values | ranges::to<QVector<double>>);
}


}// namespace pg
