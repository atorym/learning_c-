//
// Created by dym on 09.11.23.
//

#pragma once

#include <unordered_map>

#include <QColor>
#include <QObject>
#include <QVariant>

#include <plotter/core/Singleton.hpp>

#include <plotter/FuncFactory.hpp>


namespace lc {


class FuncModel final : public QObject
    , public Singleton<FuncModel> {
  Q_OBJECT
public:
  enum class Role : std::uint8_t {
    color,
  };
  Q_ENUM(Role)

public:
  ~FuncModel() override;

  QVariant      get(FuncFactory::FuncPtr const& ptr, Role role) const;
  Q_SLOT void   set(FuncFactory::FuncPtr ptr, Role role, QVariant value);
  Q_SIGNAL void changed(FuncFactory::FuncPtr, Role, QVariant, QPrivateSignal) const;

private:
  struct Attribute final {
    QColor color;
  };

private:
  FuncModel();

private:
  std::unordered_map<FuncFactory::FuncPtr, Attribute> data_;

  friend Singleton<FuncModel>;
};


}// namespace lc
