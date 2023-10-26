//
// Created by dym on 24.10.23.
//

#include <pswgen/GenPage.hpp>

#include <cassert>
#include <sstream>

#include <QClipboard>
#include <QTextBlock>

#include <pswgen/impl.hpp>

#include "ui_AboutForm.h"
#include "ui_GenPage.h"


namespace pg {


GenPage::~GenPage() = default;


GenPage::GenPage(QWidget* parent, Qt::WindowFlags f)
    : QWidget{parent, f}
    , ui{new Ui::GenPage} {

  ui->setupUi(this);

  QObject::connect(ui->pte_out, &QPlainTextEdit::textChanged, this, [this] {
    ui->pb_copy->setEnabled(!ui->pte_out->document()->isEmpty());
  });

  on_cb_auto_update_toggled(ui->cb_auto_update->isChecked());
}


ImplContext GenPage::collectContext(std::ostream& os) const {
  return {
    .manual_set = [this] {
      auto const in = ui->gb_preset->le_manual->text();
      return in | ranges::views::transform(std::bind_front(&QChar::toLatin1)) | ranges::to<std::vector<char>>;
    }(),
    .range = {
      .min = static_cast<std::size_t>(ui->gb_capacity->sb_length_min->value()),
      .max = static_cast<std::size_t>(ui->gb_capacity->sb_length_max->value()),
    },
    .count      = static_cast<std::size_t>(ui->gb_capacity->sb_count->value()),
    .os_display = os,
    .mode       = ranges::fold_left(std::array{
                                std::pair{ui->gb_preset->rb_number, ImplContext::number},
                                std::pair{ui->gb_preset->rb_letter, ImplContext::letter},
                                std::pair{ui->gb_preset->rb_upper, ImplContext::upper},
                                std::pair{ui->gb_preset->rb_character, ImplContext::character},
                                std::pair{ui->gb_preset->rb_manual, ImplContext::manual},
                              },
            ImplContext::Mode{}, [](ImplContext::Mode out, auto pair) {
        return static_cast<ImplContext::Mode>(out | (pair.first->isChecked() ? pair.second : 0));
      }),
  };
}


void GenPage::auto_generate_cons_update(bool connect) {
  if (connect) {
    assert(!auto_generate_con_);
    auto_generate_con_.emplace(QObject::connect(ui->gb_preset, &PresetBox::some_changed, this, &GenPage::send));
  } else {
    assert(auto_generate_con_);
    QObject::disconnect(auto_generate_con_.value());
    auto_generate_con_.reset();
  }
}


void GenPage::send() const {
  std::ostringstream os;
  impl(collectContext(os));
  ui->pte_out->setPlainText(QString::fromStdString(std::move(os).str()));
}


void GenPage::on_pb_regenerate_released() const {
  assert(!ui->pb_regenerate->isChecked());
  send();
}


void GenPage::on_cb_auto_update_toggled(bool f) {
  auto_generate_cons_update(f);
}


void GenPage::on_pb_copy_released() const {
  auto const doc = ui->pte_out->document();
  assert(!doc->isEmpty());
  qApp->clipboard()->setText(doc->findBlockByLineNumber(0).text());
}


void GenPage::on_pb_about_released() const {
  QDialog       form;
  Ui::AboutForm ui_form;
  ui_form.setupUi(&form);
  form.setWindowTitle("About " + windowTitle());
  form.exec();
}


}// namespace pg