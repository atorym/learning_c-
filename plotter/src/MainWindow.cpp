//
// Created by adm on 22.10.2023.
//

#include <plotter/MainWindow.hpp>

#include "ui_MainWindow.h"


namespace lc {


MainWindow::~MainWindow() = default;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow} {
  ui->setupUi(this);
  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);
}


}// namespace lc
