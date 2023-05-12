#ifndef FUSEKISERVERSETTING_H
#define FUSEKISERVERSETTING_H

#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>

#include <mainsettings.h>
#include <swidget.h>

class FusekiServerSetting : public SWidget
{
    Q_OBJECT
public:
    SWidgetTypes typeSWidget() override { return FusekiServerWindowType; }

    explicit FusekiServerSetting( QWidget* parent = nullptr );

private slots:
    void listAdd();
    void listRemove();
    void saveSettings();
    void closeWindow();
    void testSettings();

signals:
    void ERROR( QString );

private:
    void createWidget();
    void loadSettings();

private:
    QLineEdit* line_edit_link;
    QListView* list_view_prefixes;
    QLineEdit* line_ip_fuseki;
    QLineEdit* line_port_fuseki;
    QStandardItemModel* model;

    MainSettingsMaster master;
};

#endif // FUSEKISERVERSETTING_H
