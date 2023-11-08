//
// Created by dym on 04.11.23.
//

#include <plotter/ListFunc.hpp>

#include <QApplication>
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QRadioButton>
#include <QToolButton>
#include <QWidget>

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
  FuncFactory::FuncPtr const fn;

public:
  Element(QWidget* parent, FuncFactory::FuncPtr fnIn)
      : QWidget{parent}
      , fn{std::move(fnIn)}
      , btn_{new QRadioButton{this}} {
    auto const la_root = new QVBoxLayout{this};
    la_root->setMargin(0);
    la_root->setSpacing(0);

    {
      auto const la = new QHBoxLayout;
      la_root->addLayout(la);

      btn_->setText(QString::fromWCharArray(fn->name.data(), static_cast<int>(fn->name.size())));
      QObject::connect(btn_, &QAbstractButton::toggled, this, std::bind_front(&Element::funcToggled, this, QPrivateSignal{}));
      la->addWidget(btn_);

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

  bool isActive() const {
    return btn_->isChecked();
  }

signals:
  void funcToggled(QPrivateSignal) const;

private:
  QRadioButton* const btn_;
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

  for (auto const& func : FuncFactory::get()) {
    auto const la = new QHBoxLayout;
    la_->addLayout(la);

    auto const elem = new _::Element{root_, func};
    QObject::connect(elem, &_::Element::funcToggled, this, &ListFunc::onFuncToggled);
    la->addWidget(elem);
  }

  la_->addStretch();
}


void ListFunc::updateElapsed(lc::FuncFactory::FuncPtr fn, std::size_t us) {
}


void ListFunc::onFuncToggled() const {
  namespace rv    = ranges::views;
  auto const list = findChildren<_::Element const*>();

  emit selectedFunction(list
      | rv::filter([](auto const e) {
          return e->isActive();
        })
      | rv::transform([](auto const e) {
          return e->fn;
        })
      | ranges::to<QVector<lc::FuncFactory::FuncPtr>>,
    {});
}


}// namespace lc


#include "ListFunc.moc"
