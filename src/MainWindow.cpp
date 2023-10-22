//
// Created by adm on 22.10.2023.
//

#include <MainWindow.hpp>

#include "ui_MainWindow.h"


namespace pg {


MainWindow::~MainWindow() = default;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow} {

  ui->setupUi(this);
  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);
}


}// namespace pg
