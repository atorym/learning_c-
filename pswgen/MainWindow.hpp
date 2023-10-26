//
// Created by adm on 22.10.2023.
//

#pragma once

#include <QMainWindow>
#include <QScopedPointer>


namespace Ui {
class MainWindow;
}


namespace pg {


class MainWindow final : public QMainWindow {
  Q_OBJECT
public:
  ~MainWindow() override;
  MainWindow(QWidget* parent = nullptr);

private:
  QScopedPointer<Ui::MainWindow> const ui;
};


}// namespace pg
