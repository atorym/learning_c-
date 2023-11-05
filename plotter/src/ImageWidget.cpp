//
// Created by dym on 24.10.23.
//

#include <plotter/ImageWidget.hpp>

#include <QPainter>


namespace lc {


ImageWidget::~ImageWidget() = default;


ImageWidget::ImageWidget(QWidget* parent, Qt::WindowFlags f)
    : QFrame{parent, f} {
}


void ImageWidget::setPixmap(QPixmap pixmap) {
  pix_ = std::move(pixmap);
  update();
}


void ImageWidget::paintEvent(QPaintEvent* event) {
  QFrame::paintEvent(event);

  if (!pix_.isNull()) {
    QPixmap const scaledPixmap = pix_.scaled(size(), Qt::KeepAspectRatio);
    QPainter{this}.drawPixmap(
      QPoint{(size().width() - scaledPixmap.width()) / 2, (size().height() - scaledPixmap.height()) / 2},
      scaledPixmap);
  }
}


}// namespace lc
