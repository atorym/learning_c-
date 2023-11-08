//
// Created by dym on 05.11.23.
//

#pragma once

#include <QDialog>


namespace Ui {
class AboutForm;
}


namespace lc {


class AboutForm final : public QDialog {
  Q_OBJECT
public:
  ~AboutForm() override;
  AboutForm(QWidget* parent = nullptr);

private:
  QScopedPointer<Ui::AboutForm> const ui;
};


}// namespace lc
