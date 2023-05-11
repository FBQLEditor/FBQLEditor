#include "downloader.h"

#include <QDir>

#define DOWNLOAD_PATH QString( "Download" )

Downloader::Downloader( QObject* parent )
    : QThread( parent )
{
    // Инициализируем менеджер ...
    manager = new QNetworkAccessManager();
    // ... и подключаем сигнал о завершении получения данных к обработчику полученного ответа
    connect( manager, &QNetworkAccessManager::finished, this, &Downloader::onResult );
    QDir().mkdir( DOWNLOAD_PATH );
}

void Downloader::getData( const QStringList& links )
{
    links_for_download = links;
    if ( links_for_download.empty() )
    {
        emit onReady(); // Посылаем сигнал о завершении получения файла
        return;
    }

    QUrl url( links_for_download.first() ); // URL, к которому будем получать данные
    filename_for_download = DOWNLOAD_PATH + "/" + links_for_download.first().split( "/" ).last();
    links_for_download.pop_front();
    QNetworkRequest request; // Отправляемый запрос
    request.setUrl( url );   // Устанавлвиваем URL в запрос
    manager->get( request ); // Выполняем запрос
}

void Downloader::onResult( QNetworkReply* reply )
{
    // Если в процесе получения данных произошла ошибка
    if ( reply->error() )
    {
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
        emit ERROR( reply->errorString() );
    }
    else
    {
        // В противном случае создаём объект для работы с файлом
        QFile* file = new QFile( filename_for_download );
        // Создаём файл или открываем его на перезапись ...
        if ( file->open( QFile::WriteOnly ) )
        {
            file->write( reply->readAll() ); // ... и записываем всю информацию со страницы в файл
            file->close();                   // закрываем файл
            qDebug() << "Downloading is completed";
        }
        getData( links_for_download );
    }
}
