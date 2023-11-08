//
// Created by dym on 24.10.23.
//

#pragma once

#include <QFrame>
#include <QPixmap>


namespace lc {


class ImageWidget final : public QFrame {
  Q_OBJECT
public:
  ~ImageWidget() override;
  ImageWidget(QWidget* parent = {}, Qt::WindowFlags f = {});

public slots:
  void setPixmap(QPixmap pixmap);

protected:
  void paintEvent(QPaintEvent* event) override;

private:
  QPixmap pix_;
};


}// namespace lc
