//
// Created by dym on 04.11.23.
//

#include <plotter/FuncSelector.hpp>

#include <QApplication>
#include <QBoxLayout>
#include <QColorDialog>
#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QRadioButton>
#include <QToolButton>
#include <QWidget>

#include <plotter/FuncModel.hpp>


namespace lc {
namespace {
namespace _ {


class ColorViewport final : public QToolButton {
  Q_OBJECT
public:
  ColorViewport(FuncFactory::FuncPtr fn, QWidget* parent = {})
      : QToolButton{parent}
      , fn_{std::move(fn)}
      , color_{FuncModel::instance()->get(fn_, FuncModel::Role::color).value<QColor>()} {

    QObject::connect(this, &ColorViewport::colorChanged, FuncModel::instance(), [this](QColor color) {
      FuncModel::instance()->set(fn_, FuncModel::Role::color, std::move(color));
    });

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
    if (auto cnew = QColorDialog::getColor(color_, this, "Color for plot '" + QString::fromWCharArray(fn_->name.data(), fn_->name.size()) + "'"); color_ != cnew) {
      color_ = std::move(cnew);
      repaint();
      emit colorChanged(color_, {});
    }
  }

private:
  FuncFactory::FuncPtr const fn_;
  QColor                     color_;
};


class Element final : public QWidget {
  Q_OBJECT
public:
  FuncFactory::FuncPtr const fn;

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

      la->addWidget(colorViewport_);
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
  QRadioButton* const  btn_           = new QRadioButton{this};
  ColorViewport* const colorViewport_ = new ColorViewport{fn, this};
  QFrame* const        elapsed_frame_ = new QFrame{this};
  QLabel* const        elapsed_label_ = new QLabel{elapsed_label_default_text_, elapsed_frame_};
};


}// namespace _
}// namespace


FuncSelector::~FuncSelector() = default;


FuncSelector::FuncSelector(QWidget* parent)
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
    QObject::connect(elem, &_::Element::funcToggled, this, &FuncSelector::onFuncToggled);
    la->addWidget(elem);
  }

  la_->addStretch();
}


void FuncSelector::updateElapsed(FuncFactory::FuncPtr fn, std::size_t us) {
  auto const list = findChildren<_::Element const*>();
  (*ranges::find(list, fn, std::bind_front(&_::Element::fn)))->setElapsed(QString::number(us) + "μs");
}


void FuncSelector::onFuncToggled() const {
  namespace rv    = ranges::views;
  auto const list = findChildren<_::Element const*>();

  emit selectedFunction(list
      | rv::filter([](auto const e) {
          return e->isActive();
        })
      | rv::transform(std::bind_front(&_::Element::fn))
      | ranges::to<QVector<FuncFactory::FuncPtr>>,
    {});
}


}// namespace lc


#include "FuncSelector.moc"
