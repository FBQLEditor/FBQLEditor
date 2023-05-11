#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QVariant>
#include <QStandardPaths>

#define SETTINGS_PATH "configuration.set"

class MainSettingsMaster
{
private:
    QMap<QString, QVariant> settings;
    QString path_to_file;

public:
    MainSettingsMaster()
    {
        path_to_file = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + SETTINGS_PATH;
        loadSettings();
    };

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
        QFile file( path_to_file );
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

    void loadSettings()
    {
        QFile file( path_to_file );
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
    }
};

#endif // MAINSETTINGS_H
