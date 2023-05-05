#ifndef FUSEKISERVERSETTING_H
#define FUSEKISERVERSETTING_H

#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>

#include <mainsettings.h>
#include <myprocess.h>
#include <swidget.h>

class FusekiServerSetting : public SWidget
{
    Q_OBJECT
public:
    SWidgetTypes typeSWidget() override { return FusekiServerWindowType; }

    explicit FusekiServerSetting( QWidget* parent = nullptr );
    ~FusekiServerSetting();

    void createWidget();

private slots:
    void startFuseki();
    void testConnectToPage();
    void setLinkPage();
    void openFuseki();
    void testStart();
    void listAdd();
    void listRemove();

signals:
    void ERROR( QString );
    void runCommand( QString );
    void stopCommand();

private:
    QPushButton* button_start;
    QLineEdit* line_edit_link;
    QListView* list_view_prefixs;
    QStandardItemModel* model;

    MyProcess* process;
    bool flag_started = false;
};

#endif // FUSEKISERVERSETTING_H
