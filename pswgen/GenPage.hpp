//
// Created by dym on 24.10.23.
//

#pragma once

#include <iosfwd>
#include <optional>

#include <QScopedPointer>
#include <QWidget>


namespace Ui {
class GenPage;
}


namespace pg {


struct ImplContext;


class GenPage final : public QWidget {
  Q_OBJECT
public:
  ~GenPage() override;
  GenPage(QWidget* parent = nullptr, Qt::WindowFlags f = {});

  ImplContext collectContext(std::ostream& os) const;

private:
  void auto_generate_cons_update(bool connect);

private slots:
  void send() const;
  void on_cb_auto_update_toggled(bool f);
  void on_pb_regenerate_released() const;
  void on_pb_copy_released() const;
  void on_pb_about_released() const;

private:
  QScopedPointer<Ui::GenPage> const      ui;
  std::optional<QMetaObject::Connection> auto_generate_con_;
};


}// namespace pg