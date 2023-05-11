#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QDebug>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QThread>
#include <QUrl>

class Downloader : public QThread
{
    Q_OBJECT
public:
    explicit Downloader( QObject* parent = 0 );

signals:
    void onReady();
    void ERROR( QString );

public slots:
    void getData( const QStringList& links ); // Метод инициализации запроса на получение данных
    void onResult( QNetworkReply* reply );    // Слот обработки ответа о полученных данных

private:
    QNetworkAccessManager* manager; // менеджер сетевого доступа
    QString filename_for_download;
    QStringList links_for_download;
};

#endif // DOWNLOADER_H
