//
// Created by dym on 05.11.23.
//

#include <plotter/core/NetworkAccess.hpp>

#include <QNetworkAccessManager>


namespace lc {


NetworkAccess::~NetworkAccess() {
  manager_->deleteLater();
}


NetworkAccess::NetworkAccess()
    : manager_{new QNetworkAccessManager} {
}


}// namespace lc
