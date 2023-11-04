//
// Created by dym on 24.10.23.
//

#pragma once

#include <QLabel>


namespace lc {


// https://stackoverflow.com/a/22618496/13161739
class LabelAspectRatioPixmap final : public QLabel {
  Q_OBJECT
public:
  ~LabelAspectRatioPixmap() override;
  LabelAspectRatioPixmap(QWidget* parent = {}, Qt::WindowFlags f = {});

  int     heightForWidth(int width) const override;
  QSize   sizeHint() const override;
  QPixmap scaledPixmap() const;

public slots:
  void setPixmap(const QPixmap&) /*override !!!*/;

protected:
  void resizeEvent(QResizeEvent*) override;

private:
  QPixmap pix_;
};


}// namespace lc
