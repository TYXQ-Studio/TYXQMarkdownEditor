//
// Created by xiaob on 2022/12/4.
//

#include "settings.h"
#include <QtCore/qsettings.h>
#include <QtCore/qcoreapplication.h>
#include <QtCore/qfileinfo.h>
#include <framelesshelpercore_global.h>

static QScopedPointer<QSettings> g_settings;

[[nodiscard]] static inline QSettings *appConfigFile()
{
    const QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    const QString iniFileName = fileInfo.completeBaseName() + FRAMELESSHELPER_STRING_LITERAL(".ini");
    const QString iniFilePath = fileInfo.canonicalPath() + u'/' + iniFileName;
    return new QSettings(iniFilePath, QSettings::IniFormat);
}

[[nodiscard]] static inline QString appKey(const QString &id, const QString &key)
{
    Q_ASSERT(!key.isEmpty());
    if (key.isEmpty()) {
        return {};
    }
    return (id.isEmpty() ? key : (id + u'/' + key));
}

void Settings::set(const QString &id, const QString &key, const QByteArray &data)
{
    Q_ASSERT(!key.isEmpty());
    Q_ASSERT(!data.isEmpty());
    if (key.isEmpty() || data.isEmpty()) {
        return;
    }
    if (g_settings.isNull()) {
        g_settings.reset(appConfigFile());
    }
    g_settings->setValue(appKey(id, key), data);
}

QByteArray Settings::get(const QString &id, const QString &key)
{
    Q_ASSERT(!key.isEmpty());
    if (key.isEmpty()) {
        return {};
    }
    if (g_settings.isNull()) {
        g_settings.reset(appConfigFile());
    }
    return g_settings->value(appKey(id, key)).toByteArray();
}
