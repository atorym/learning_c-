//
// Created by dym on 04.11.23.
//

#include <plotter/ListFunc.hpp>

#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QApplication>
#include <QPushButton>
#include <QRadioButton>
#include <QToolButton>
#include <QWidget>

#include <plotter/FuncFactory.hpp>
#include <plotter/colorAppointer.hpp>


namespace lc {
namespace {
namespace _ {


class ColorViewport final : public QToolButton {
  Q_OBJECT

public:
  using QToolButton::QToolButton;

protected:
  void paintEvent(QPaintEvent* event) override {
    QToolButton::paintEvent(event);

    QPainter painter{this};
    painter.setPen(color_);
    painter.setBrush(color_);
    int constexpr margin = 5;
    painter.drawRect(rect().adjusted(margin, margin, -(margin + 1), -(margin + 1)));
  }

private:
  QColor color_ = QString::fromStdString(colorAppointer());
};


class Element final : public QWidget {
  Q_OBJECT
public:
  Element(QWidget* parent, QString const& name)
      : QWidget{parent} {
    auto const la_root = new QVBoxLayout{this};
    la_root->setMargin(0);
    la_root->setSpacing(0);

    {
      auto const la = new QHBoxLayout;
      la_root->addLayout(la);

      auto const btn = new QRadioButton{this};
      btn->setText(name);
      QObject::connect(btn, &QAbstractButton::toggled, this, [this](bool checked) {
        //      auto const btn = qobject_cast<QAbstractButton*>(sender());
        //      qDebug() << btn->text() << checked;
        if (checked) {
          emit funcEnabled({});
        }
      });
      la->addWidget(btn);

      la->addStretch();

      la->addWidget(new ColorViewport{this});
    }

    {
      auto const la = new QHBoxLayout;
      la_root->addLayout(la);

      {
        auto const elapsed_frame = new QFrame{this};
        elapsed_frame->setFrameShape(QFrame::StyledPanel);
        la->addWidget(elapsed_frame);

        auto const elapsed_la = new QVBoxLayout{elapsed_frame};
        elapsed_la->setMargin(1);

        auto const elapsed = new QLabel{"test", elapsed_frame};
        elapsed->setFont(qApp->font());
        elapsed_la->addWidget(elapsed);
      }

      la->addStretch();
    }
  }

signals:
  void funcEnabled(QPrivateSignal) const;
};


}// namespace _
}// namespace


ListFunc::~ListFunc() = default;


ListFunc::ListFunc(QWidget* parent)
    : QScrollArea{parent}
    , root_{new QWidget{this}}
    , la_{new QVBoxLayout{root_}} {

  la_->setSpacing(9);

  setWidgetResizable(true);
  setWidget(root_);

  for (auto const& [i, func] : FuncFactory::get() | ranges::views::enumerate) {
    auto const la = new QHBoxLayout;
    la_->addLayout(la);

    auto const elem = new _::Element{root_, QString::fromWCharArray(func.name.data(), static_cast<int>(func.name.size()))};
    QObject::connect(elem, &_::Element::funcEnabled, this, [this, index = i] {
      emit selectedFunction(index, {});
    });
    la->addWidget(elem);
  }

  la_->addStretch();
}


void ListFunc::updateElapsed(std::size_t index) {
}


}// namespace lc


#include "ListFunc.moc"
