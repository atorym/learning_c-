//
// Created by dym on 24.10.23.
//

#include <GenPage.hpp>

#include <cassert>

#include <QClipboard>
#include <QTextBlock>

#include <impl.hpp>

#include "ui_AboutForm.h"


namespace pg {


GenPage::~GenPage() = default;


GenPage::GenPage(QWidget* parent, Qt::WindowFlags f)
    : QWidget{parent, f} {

  setupUi(this);

  QObject::connect(pte_out, &QPlainTextEdit::textChanged, pb_copy, [pb = pb_copy, edit = pte_out] {
    pb->setEnabled(!edit->document()->isEmpty());
  });

  on_cb_auto_update_toggled(cb_auto_update->isChecked());
}


void GenPage::auto_generate_cons_update(bool connect) {
  if (connect) {
    assert(!auto_generate_con_);
    auto_generate_con_.emplace(QObject::connect(gb_preset, &PresetBox::some_changed, this, &GenPage::send));
  } else {
    assert(auto_generate_con_);
    QObject::disconnect(auto_generate_con_.value());
    auto_generate_con_.reset();
  }
}


void GenPage::send() const {
  std::ostringstream oss;
  impl({
    .manual_set = [this] {
      auto const in = gb_preset->le_manual->text();
      return in | ranges::views::transform(std::bind_front(&QChar::toLatin1)) | ranges::to<std::vector<char>>;
    }(),
    .range = {
      .min = static_cast<std::size_t>(gb_capacity->sb_length_min->value()),
      .max = static_cast<std::size_t>(gb_capacity->sb_length_max->value()),
    },
    .count      = static_cast<std::size_t>(gb_capacity->sb_count->value()),
    .os_display = oss,
    .mode       = ranges::fold_left(std::array{
                                std::pair{gb_preset->rb_number, ImplContext::number},
                                std::pair{gb_preset->rb_letter, ImplContext::letter},
                                std::pair{gb_preset->rb_upper, ImplContext::upper},
                                std::pair{gb_preset->rb_character, ImplContext::character},
                                std::pair{gb_preset->rb_manual, ImplContext::manual},
                              },
            ImplContext::Mode{}, [](ImplContext::Mode out, auto pair) {
        return static_cast<ImplContext::Mode>(out | (pair.first->isChecked() ? pair.second : 0));
      }),
  });
  pte_out->setPlainText(QString::fromStdString(std::move(oss).str()));
}


void GenPage::on_pb_regenerate_released() const {
  assert(!pb_regenerate->isChecked());
  send();
}


void GenPage::on_cb_auto_update_toggled(bool f) {
  auto_generate_cons_update(f);
}


void GenPage::on_pb_copy_released() const {
  auto const doc = pte_out->document();
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