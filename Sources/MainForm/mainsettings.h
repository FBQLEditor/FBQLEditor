#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QFile>
#include <QMap>
#include <QVariant>

#define SETTINGS_PATH "configuration.json"

namespace MainSettings
{
static QMap<QString, QVariant> settings;

template <typename T>
static void setSetting( QString tag, T data )
{
    MainSettings::settings.insert( tag, data );
}

template <typename T>
static T getSettings( QString tag )
{
    auto it = MainSettings::settings.find( tag );
    if ( MainSettings::settings.end() != it )
    {
        return it->value<T>();
    }
    return {};
}
} // namespace MainSettings
#endif // MAINSETTINGS_H
