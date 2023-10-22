//
// Created by dym on 24.10.23.
//

#pragma once

#include <optional>

#include <QWidget>

#include "ui_GenPage.h"


namespace pg {


class GenPage final : public QWidget
    , public Ui::GenPage {
  Q_OBJECT
public:
  ~GenPage() override;
  GenPage(QWidget* parent = nullptr, Qt::WindowFlags f = {});

private:
  void auto_generate_cons_update(bool connect);

private slots:
  void send() const;
  void on_cb_auto_update_toggled(bool f);
  void on_pb_regenerate_released() const;
  void on_pb_copy_released() const;
  void on_pb_about_released() const;

private:
  std::optional<QMetaObject::Connection> auto_generate_con_;
};


}// namespace pg