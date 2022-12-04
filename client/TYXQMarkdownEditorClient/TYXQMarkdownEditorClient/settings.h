//
// Created by xiaob on 2022/12/4.
//

#ifndef TYXQMARKDOWNEDITORCLIENT_SETTINGS_H
#define TYXQMARKDOWNEDITORCLIENT_SETTINGS_H

#include <QtCore/qstring.h>

namespace Settings
{
    void set(const QString &id, const QString &key, const QByteArray &data);
    [[nodiscard]] QByteArray get(const QString &id, const QString &key);
} // namespace Settings


#endif //TYXQMARKDOWNEDITORCLIENT_SETTINGS_H
