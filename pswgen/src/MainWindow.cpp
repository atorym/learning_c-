//
// Created by adm on 22.10.2023.
//

#include <pswgen/MainWindow.hpp>

#include <cassert>

#include <pswgen/impl.hpp>

#include "ui_MainWindow.h"


namespace pg {


MainWindow::~MainWindow() = default;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow} {

  ui->setupUi(this);
  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);

  QObject::connect(ui->distribution, &DistributionPage::initPreset, this, [this](DistributionPage::PresetForSamples* preset) {
    assert(preset);
    assert(!preset->ctx);
    preset->ctx = std::make_shared<ImplContext>(ui->gen->collectContext(preset->is));
  });
}


}// namespace pg
