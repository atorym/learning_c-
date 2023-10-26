//
// Created by dym on 24.10.23.
//

#include <functional>
#include <memory>

#include <QMetaType>


Q_DECLARE_METATYPE(std::shared_ptr<std::function<void()>>)
Q_DECLARE_METATYPE(std::shared_ptr<std::function<void()> const>)
