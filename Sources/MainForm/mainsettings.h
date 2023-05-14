#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QStandardPaths>
#include <QVariant>

#define SETTINGS_PATH "FBQL Settings.fbs"

class MainSettingsMaster
{
private:
    QMap<QString, QMap<QString, QVariant>> settings;
    QString path_to_file;
    QString data_context;

public:
    MainSettingsMaster( const QString& context )
    {
        data_context = context;
        path_to_file = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) + "/" + SETTINGS_PATH;
        loadSettings();
    };

    template <typename T>
    void setSetting( const QString& tag, const T& data )
    {
        setSetting( data_context, tag, data );
    }

    template <typename T>
    void setSetting( const QString& context, const QString& tag, const T& data )
    {
        settings[context][tag] = data;
        saveSettings();
    }

    template <typename T>
    T getSettings( const QString& tag )
    {
        return getSettings<T>( data_context, tag );
    }

    template <typename T>
    T getSettings( const QString& context, const QString& tag )
    {
        loadSettings();
        auto it_context = settings.find( context );
        if ( settings.end() != it_context )
        {
            auto it_tag = it_context->find( tag );
            if ( it_context->end() != it_tag )
            {
                return it_tag->value<T>();
            }
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
