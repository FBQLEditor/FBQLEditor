#ifndef SOPENSAVEPROCESSOR_H
#define SOPENSAVEPROCESSOR_H

#include <QMenu>
#include <QObject>

#include <swidget.h>

class SOpenSaveProcessor : public QObject
{
    Q_OBJECT
public:
    explicit SOpenSaveProcessor( QMenu* context_menu, QWidget* parent = nullptr );

    void openFBAndCreateWidget();

signals:
    void widgetCreate( SWidget*, QString );

private:
    QWidget* my_parent;
    QMenu* context_menu;

    QString folder_default;
    QString folder_users;
};

#endif // SOPENSAVEPROCESSOR_H
