#ifndef STABWIDGET_H
#define STABWIDGET_H

#include <QMap>
#include <QTabWidget>

#include <sgraphicsview.h>

class STabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit STabWidget( QWidget* parent = nullptr );

    QVector<DiagramItem*> getBlocksForRun();
    SWidget* currentSWidget();

public slots:
    void addWidget( SWidget* widget, const QString& name );
    void itemForAdd( DiagramItemSettings* );
    void resetBlocks();
    void deleteItemOnScene();
    void setTabName( QString );
    void callSaveCurrentWidget();

private:
    void createTabWidgets();

private slots:
    void slotOnSignalCloseWidget();
    void tabClose( int );
    void slotCurrentTab( int );

signals:
    void newCurrentMode( int );
    void ERROR( QString );

private:
    QMap<QWidget*, int> widget_lib;
};

#endif // STABWIDGET_H
