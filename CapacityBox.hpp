//
// Created by dym on 24.10.23.
//

#pragma once

#include <QGroupBox>

#include "ui_CapacityBox.h"


namespace pg {


class CapacityBox final : public QGroupBox
    , public Ui::CapacityBox {
  Q_OBJECT
public:
  ~CapacityBox() override;
  CapacityBox(QWidget* parent = nullptr);
};


}// namespace pg
