//
// Created by dym on 24.10.23.
//

#include <plotter/AspectRatioPixmap.hpp>


namespace lc {


AspectRatioPixmap::~AspectRatioPixmap() = default;


AspectRatioPixmap::AspectRatioPixmap(QWidget* parent, Qt::WindowFlags f)
    : QLabel{parent, f} {
  setMinimumSize(40, 40);
  setScaledContents(false);
}


void AspectRatioPixmap::setPixmap(const QPixmap& p) {
  pix_ = p;
  if (!pix_.isNull()) {
    QLabel::setPixmap(scaledPixmap());
  }
}


int AspectRatioPixmap::heightForWidth(int width) const {
  return pix_.isNull() ? height() : (static_cast<qreal>(pix_.height()) * width) / pix_.width();
}


QSize AspectRatioPixmap::sizeHint() const {
  auto const w = width();
  return {w, heightForWidth(w)};
}


QPixmap AspectRatioPixmap::scaledPixmap() const {
  return pix_.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}


void AspectRatioPixmap::resizeEvent(QResizeEvent* e) {
  if (!pix_.isNull()) {
    QLabel::setPixmap(scaledPixmap());
  }
}


}// namespace lc
