//
// Created by dym on 05.11.23.
//

#include <plotter/AboutForm.hpp>

#include <cassert>
#include <tuple>
#include <unordered_map>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include <plotter/core/NetworkAccess.hpp>
#include <plotter/core/Singleton.hpp>

#include "ui_AboutForm.h"


namespace lc {
namespace {
namespace _ {


class Pixmaps final : public Singleton<Pixmaps> {
public:
  static void bind(QUrl url, auto* context, auto&& slot) {
    instance()->bind_impl(std::move(url), context, std::forward<decltype(slot)>(slot));
  }

private:
  Pixmaps() = default;

  void bind_impl(QUrl url, auto* context, auto&& slot) {
    assert(context);

    if (auto const it = map_.find(url); it != map_.cend()) {
      slot(it->second);
      return;
    }

    auto const reply = NetworkAccess::manager()->get(QNetworkRequest{url});
    QObject::connect(reply, &QNetworkReply::finished, context, [this, slot = std::tuple{std::forward<decltype(slot)>(slot)}, url, reply]() mutable {
      assert(reply->error() == QNetworkReply::NoError);

      QPixmap pixmap;
      pixmap.loadFromData(reply->readAll());
      {
        auto const [it, f] = map_.emplace(url, pixmap);
        assert(f);
      }

      std::get<0>(std::move(slot))(std::move(pixmap));
      reply->deleteLater();
    });
  }

private:
  std::unordered_map<QUrl, QPixmap, decltype([](auto&& url) {
    return qHash(url);
  })>
    map_;

  friend Singleton<Pixmaps>;
};


}// namespace _
}// namespace


AboutForm::~AboutForm() = default;


AboutForm::AboutForm(QWidget* parent)
    : QDialog{parent}
    , ui{new Ui::AboutForm} {
  ui->setupUi(this);

  for (auto const [label, url] : {
         std::pair{ui->l_conelove, "https://avatars.githubusercontent.com/u/73636252?v=4"},
         std::pair{ui->l_atorym, "https://avatars.githubusercontent.com/u/73040280?v=4"},
       }) {
    _::Pixmaps::bind({url}, this, [l = label](auto&& pixmap) {
      l->setPixmap(std::forward<decltype(pixmap)>(pixmap));
    });
  }
}


}// namespace lc
