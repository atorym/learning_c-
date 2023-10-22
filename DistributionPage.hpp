//
// Created by dym on 24.10.23.
//

#pragma once

#include <memory>
#include <unordered_map>

#include <QWidget>

#include "ui_DistributionPage.h"


namespace pg {


class DistributionPage final : public QWidget
    , public Ui::DistributionPage {
  Q_OBJECT
public:
public:
  ~DistributionPage() override;
  DistributionPage(QWidget* parent = nullptr);

public slots:
  void updateDistribution(std::shared_ptr<std::unordered_map<char, std::size_t> const> map);

private:
  QCPBars* const bars_;
};


}// namespace pg
