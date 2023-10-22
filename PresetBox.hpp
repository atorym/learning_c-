//
// Created by dym on 23.10.23.
//

#pragma once

#include <QGroupBox>

#include "ui_PresetBox.h"


namespace pg {


class PresetBox final : public QGroupBox
    , public Ui::PresetBox {
  Q_OBJECT
public:
  ~PresetBox() override;
  PresetBox(QWidget* parent = nullptr);

signals:
  void some_changed(QPrivateSignal) const;
};


}// namespace pg
