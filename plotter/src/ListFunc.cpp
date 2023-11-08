//
// Created by dym on 04.11.23.
//

#include <plotter/ListFunc.hpp>

#include <QApplication>
#include <QBoxLayout>
#include <QColorDialog>
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
  ColorViewport(QString name, QWidget* parent = {})
      : QToolButton{parent}
      , name_{std::move(name)} {

    QObject::connect(this, &QAbstractButton::released, this, &ColorViewport::open_dialog);
  }


  QColor const& color() const {
    return color_;
  }

signals:
  void colorChanged(QColor, QPrivateSignal) const;

protected:
  void paintEvent(QPaintEvent* event) override {
    QToolButton::paintEvent(event);

    QPainter painter{this};
    painter.setPen(color_);
    painter.setBrush(color_);
    int constexpr margin = 5;
    painter.drawRect(rect().adjusted(margin, margin, -(margin + 1), -(margin + 1)));
  }

private slots:
  void open_dialog() {
    if (auto cnew = QColorDialog::getColor(color_, this, "Color for plot '" + name_ + "'"); color_ != cnew) {
      color_ = std::move(cnew);
      repaint();
      emit colorChanged(color_, {});
    }
  }

private:
  QString name_;
  QColor  color_ = QString::fromStdString(colorAppointer());
};


class Element final : public QWidget {
  Q_OBJECT
public:
  FuncFactory::FuncPtr const fn;
  ColorViewport* const       colorViewport = new ColorViewport{QString::fromWCharArray(fn->name.data(), fn->name.size()), this};

public:
  Element(QWidget* parent, FuncFactory::FuncPtr fnIn)
      : QWidget{parent}
      , fn{std::move(fnIn)} {
    auto const la_root = new QVBoxLayout{this};
    la_root->setMargin(0);
    la_root->setSpacing(0);

    {
      auto const la = new QHBoxLayout;
      la_root->addLayout(la);

      btn_->setText(QString::fromWCharArray(fn->name.data(), static_cast<int>(fn->name.size())));
      QObject::connect(btn_, &QAbstractButton::toggled, this, [this](bool f) {
        if (!f) {
          elapsed_label_->setText(elapsed_label_default_text_);
        }
        emit funcToggled({});
      });
      la->addWidget(btn_);

      la->addStretch();

      la->addWidget(colorViewport);
    }

    {
      auto const la = new QHBoxLayout;
      la_root->addLayout(la);

      {
        elapsed_frame_->setFrameShape(QFrame::NoFrame);
        elapsed_frame_->setToolTip("Elapsed time");
        la->addWidget(elapsed_frame_);

        auto const elapsed_la = new QVBoxLayout{elapsed_frame_};
        elapsed_la->setMargin(1);

        elapsed_label_->setFont(qApp->font());
        elapsed_la->addWidget(elapsed_label_);
      }

      la->addStretch();
    }
  }


  bool isActive() const {
    return btn_->isChecked();
  }


  void setElapsed(QString const& text) const {
    elapsed_label_->setText(text);
  }


signals:
  void funcToggled(QPrivateSignal) const;

private:
  auto static constexpr elapsed_label_default_text_ = " - ";

private:
  QRadioButton* const btn_           = new QRadioButton{this};
  QFrame* const       elapsed_frame_ = new QFrame{this};
  QLabel* const       elapsed_label_ = new QLabel{elapsed_label_default_text_, elapsed_frame_};
};


}// namespace _
}// namespace


ListFunc::~ListFunc() = default;


ListFunc::ListFunc(QWidget* parent)
    : QScrollArea{parent}
    , root_{new QWidget{this}}
    , la_{new QVBoxLayout{root_}} {

  la_->setSpacing(6);

  setWidgetResizable(true);
  setWidget(root_);

  for (auto const func : FuncFactory::get()) {
    auto const la = new QHBoxLayout;
    la_->addLayout(la);

    auto const elem = new _::Element{root_, func};
    QObject::connect(elem, &_::Element::funcToggled, this, &ListFunc::onFuncToggled);
    QObject::connect(elem->colorViewport, &_::ColorViewport::colorChanged, this, [this, func](QColor color) {
      emit colorChanged(func, color, {});
    });
    la->addWidget(elem);
  }

  la_->addStretch();
}


void ListFunc::updateElapsed(FuncFactory::FuncPtr fn, std::size_t us) {
  auto const list = findChildren<_::Element const*>();
  (*ranges::find(list, fn, std::bind_front(&_::Element::fn)))->setElapsed(QString::number(us) + "μs");
}


void ListFunc::onFuncToggled() const {
  namespace rv    = ranges::views;
  auto const list = findChildren<_::Element const*>();

  emit selectedFunction(list
      | rv::filter([](auto const e) {
          return e->isActive();
        })
      | rv::transform([](auto const e) -> FuncColorPair {
          return {
            .func  = e->fn,
            .color = e->colorViewport->color(),
          };
        })
      | ranges::to<QVector<FuncColorPair>>,
    {});
}


}// namespace lc


#include "ListFunc.moc"
