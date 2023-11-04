//
// Created by dym on 24.10.23.
//

#include <plotter/LabelAspectRatioPixmap.hpp>


namespace lc {


LabelAspectRatioPixmap::~LabelAspectRatioPixmap() = default;


LabelAspectRatioPixmap::LabelAspectRatioPixmap(QWidget* parent, Qt::WindowFlags f)
    : QLabel{parent, f} {
  setMinimumSize(40, 40);
  setScaledContents(false);
}


void LabelAspectRatioPixmap::setPixmap(const QPixmap& p) {
  pix_ = p;
  QLabel::setPixmap(scaledPixmap());
}


int LabelAspectRatioPixmap::heightForWidth(int width) const {
  return pix_.isNull() ? height() : (static_cast<qreal>(pix_.height()) * width) / pix_.width();
}


QSize LabelAspectRatioPixmap::sizeHint() const {
  auto const w = width();
  return {w, heightForWidth(w)};
}


QPixmap LabelAspectRatioPixmap::scaledPixmap() const {
  return pix_.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}


void LabelAspectRatioPixmap::resizeEvent(QResizeEvent* e) {
  if (!pix_.isNull()) {
    QLabel::setPixmap(scaledPixmap());
  }
}


}// namespace lc
