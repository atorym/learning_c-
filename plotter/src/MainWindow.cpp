//
// Created by adm on 22.10.2023.
//

#include <plotter/MainWindow.hpp>

#include <QStandardItemModel>

#include <plotter/GraphMethodRadioDelegate.hpp>

#include "ui_MainWindow.h"


namespace lc {


MainWindow::~MainWindow() = default;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , model_{new QStandardItemModel{this}} {
  model_->setRowCount(2);
  model_->setColumnCount(1);
  for (auto const data = {true, false}; auto const [i, f] : data | ranges::views::enumerate) {
    model_->setData(model_->index(i, 0), QVariant::fromValue(f));
  }

  ui->setupUi(this);
  setWindowTitle(QString{PROJECT_NAME} + " v" + PROJECT_VERSION);

  ui->lv_mode->setItemDelegate(new GraphMethodRadioDelegate{ui->lv_mode});
  ui->lv_mode->setModel(model_);
}


}// namespace lc
