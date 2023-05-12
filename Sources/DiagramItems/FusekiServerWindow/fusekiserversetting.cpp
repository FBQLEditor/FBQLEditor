#include "fusekiserversetting.h"

#include <QDesktopServices>
#include <QDir>
#include <QGridLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

FusekiServerSetting::FusekiServerSetting( QWidget* parent )
    : SWidget( parent )
{
    createWidget();
}

void FusekiServerSetting::createWidget()
{
    QLabel* label_ip_fuseki = new QLabel( "IP-adress Fuseki Server:", this );
    line_ip_fuseki = new QLineEdit( this );
    QLabel* label_port_fuseki = new QLabel( "Port Fuseki Server:", this );
    line_port_fuseki = new QLineEdit( this );
    line_port_fuseki->setValidator( new QIntValidator( 1024, 65535, this ) );

    QLabel* link_label = new QLabel( "Dataset Name: ", this );
    link_label->setMaximumHeight( 30 );
    line_edit_link = new QLineEdit( this );
    QLabel* label_prefixes = new QLabel( "Prefixes:", this );

    list_view_prefixes = new QListView( this );
    model = new QStandardItemModel();
    list_view_prefixes->setModel( model );

    QPushButton* button_list_add = new QPushButton( "Add Row", this );
    QPushButton* button_list_remove = new QPushButton( "Remove Row", this );
    QPushButton* button_save_settings = new QPushButton( "Save Settings", this );
    QPushButton* button_close_window = new QPushButton( "Close", this );
    QPushButton* button_test_settings = new QPushButton( "Test Settings", this );

    label_ip_fuseki->setMaximumWidth( 500 );
    label_port_fuseki->setMaximumWidth( 500 );
    line_ip_fuseki->setMaximumWidth( 500 );
    line_port_fuseki->setMaximumWidth( 500 );
    link_label->setMaximumWidth( 500 );
    line_edit_link->setMaximumWidth( 500 );
    label_prefixes->setMaximumWidth( 500 );
    label_prefixes->setMaximumHeight( 30 );

    list_view_prefixes->setMaximumWidth( 500 );
    list_view_prefixes->setMinimumHeight( 400 );
    list_view_prefixes->setMaximumHeight( 400 );

    button_list_add->setMaximumWidth( 240 );
    button_list_remove->setMaximumWidth( 240 );
    button_test_settings->setMaximumWidth( 500 );
    button_save_settings->setMaximumWidth( 240 );
    button_close_window->setMaximumWidth( 240 );

    connect( button_list_add, SIGNAL( clicked() ), this, SLOT( listAdd() ) );
    connect( button_list_remove, SIGNAL( clicked() ), this, SLOT( listRemove() ) );
    connect( button_save_settings, SIGNAL( clicked() ), this, SLOT( saveSettings() ) );
    connect( button_close_window, SIGNAL( clicked() ), this, SLOT( closeWindow() ) );
    connect( button_test_settings, SIGNAL( clicked() ), this, SLOT( testSettings() ) );

    QGridLayout* gridLayout = new QGridLayout( this );
    gridLayout->addWidget( new QLabel( this ), 3, 0, 1, 1 );
    gridLayout->addWidget( new QLabel( this ), 3, 3, 1, 2 );
    gridLayout->addWidget( label_ip_fuseki, 4, 3, 1, 2 );
    gridLayout->addWidget( line_ip_fuseki, 5, 3, 1, 2 );
    gridLayout->addWidget( label_port_fuseki, 6, 3, 1, 2 );
    gridLayout->addWidget( line_port_fuseki, 7, 3, 1, 2 );
    gridLayout->addWidget( link_label, 8, 3, 1, 2 );
    gridLayout->addWidget( line_edit_link, 9, 3, 1, 2 );
    gridLayout->addWidget( label_prefixes, 10, 3, 1, 2 );
    gridLayout->addWidget( list_view_prefixes, 11, 3, 1, 2 );
    gridLayout->addWidget( button_list_add, 12, 3, 1, 1 );
    gridLayout->addWidget( button_list_remove, 12, 4, 1, 1 );
    gridLayout->addWidget( new QLabel( this ), 13, 3, 1, 3 );
    gridLayout->addWidget( new QLabel( this ), 13, 5, 1, 1 );
    gridLayout->addWidget( button_test_settings, 14, 3, 1, 2 );
    gridLayout->addWidget( button_save_settings, 15, 3, 1, 1 );
    gridLayout->addWidget( button_close_window, 15, 4, 1, 1 );
}

void FusekiServerSetting::loadSettings()
{
    MainSettingsMaster master( "Fuseki" );
    line_edit_link->setText( master.getSettings<QString>( "dataset_name" ) );
    auto str_list = master.getSettings<QStringList>( "SPARQL", "prefixes" );
    for ( auto str : str_list )
    {
        model->appendRow( new QStandardItem( str ) );
    }
    line_ip_fuseki->setText( master.getSettings<QString>( "ip" ) );
    line_port_fuseki->setText( master.getSettings<QString>( "port" ) );
}

void FusekiServerSetting::listAdd()
{
    model->appendRow( new QStandardItem( "PREFIX : <>" ) );
}

void FusekiServerSetting::listRemove()
{
    model->removeRow( list_view_prefixes->currentIndex().row() );
}

void FusekiServerSetting::saveSettings()
{
    MainSettingsMaster master( "Fuseki" );
    master.setSetting( "dataset_name", line_edit_link->text() );
    QStringList str_list;
    for ( int i = 0; i < model->rowCount(); ++i )
    {
        str_list << model->item( i )->text();
    }
    master.setSetting( "SPARQL", "prefixes", str_list );
    master.setSetting( "ip", line_ip_fuseki->text() );
    master.setSetting( "port", line_port_fuseki->text() );
}

void FusekiServerSetting::closeWindow()
{
    emit signalCloseWidget();
}

void FusekiServerSetting::testSettings()
{
}
