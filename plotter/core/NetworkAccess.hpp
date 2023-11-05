//
// Created by dym on 05.11.23.
//

#pragma once

#include <plotter/core/Singleton.hpp>


class QNetworkAccessManager;


namespace lc {


class NetworkAccess final : public Singleton<NetworkAccess> {
public:
  static QNetworkAccessManager* manager() {
    return instance()->manager_;
  }

public:
  ~NetworkAccess();

private:
  NetworkAccess();

private:
  QNetworkAccessManager* const manager_;

  friend Singleton<NetworkAccess>;
};


}// namespace lc
