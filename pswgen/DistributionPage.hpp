//
// Created by dym on 24.10.23.
//

#pragma once

#include <iosfwd>
#include <memory>

#include <QMetaType>
#include <QScopedPointer>
#include <QWidget>

#include <pswgen/impl.hpp>


class QCPBars;


namespace Ui {
class DistributionPage;
}


namespace pg {


class DistributionPage final : public QWidget {
  Q_OBJECT
public:
  struct PresetForSamples final {
    std::shared_ptr<ImplContext> ctx;
    std::ostream&                is;
  };

public:
  ~DistributionPage() override;
  DistributionPage(QWidget* parent = nullptr);

signals:
  void initPreset(PresetForSamples*, QPrivateSignal) const;

private slots:
  void on_pb_run_released() const;

private:
  QScopedPointer<Ui::DistributionPage> const ui;
  QCPBars* const                             bars_;
};


}// namespace pg

Q_DECLARE_METATYPE(pg::DistributionPage::PresetForSamples*)
