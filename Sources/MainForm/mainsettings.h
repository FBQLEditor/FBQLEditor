#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QVariant>

#define SETTINGS_PATH "configuration.set"

class MainSettingsMaster
{
private:
    QMap<QString, QVariant> settings;

public:
    MainSettingsMaster() { loadSettings(); };

    template <typename T>
    void setSetting( const QString& tag, const T& data )
    {
        settings.insert( tag, data );
        saveSettings();
    }

    template <typename T>
    T getSettings( const QString& tag )
    {
        loadSettings();
        auto it = settings.find( tag );
        if ( settings.end() != it )
        {
            return it->value<T>();
        }
        return {};
    }

private:
    void saveSettings()
    {
        QFile file( SETTINGS_PATH );
        QDataStream stream( &file );

        if ( file.open( QIODevice::WriteOnly ) )
        {
            stream << settings;
        }
        else
        {
            qDebug() << "Error save settings";
        }
        file.close();
    }

    QMap<QString, QVariant> loadSettings()
    {
        QFile file( SETTINGS_PATH );
        QDataStream stream( &file );
        if ( file.open( QIODevice::ReadOnly ) )
        {
            stream >> settings;
        }
        else
        {
            qDebug() << "Error load settings";
        }
        file.close();
        return settings;
    }
};

#endif // MAINSETTINGS_H
