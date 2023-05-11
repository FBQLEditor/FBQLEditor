#include "fusekiserversetting.h"

#include <QDesktopServices>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#ifdef Q_OS_LINUX
#define FUSEKI_SERVER_PATH "./FusekiServer/fuseki-server"
#else
#define FUSEKI_SERVER_PATH "FusekiServer/fuseki-server.bat"
#endif

FusekiServerSetting::FusekiServerSetting( QWidget* parent )
    : SWidget( parent )
{
    createWidget();

    process = new MyProcess( this );
    connect( this, SIGNAL( runCommand( QString ) ), process, SLOT( runCommand( QString ) ) );
    connect( this, SIGNAL( stopCommand() ), process, SLOT( stopCommand() ) );

    line_edit_link->setText( master.getSettings<QString>( "SPARQL_dataset_name" ) );
    auto str_list = master.getSettings<QStringList>( "SPARQL_prefixs" );
    for ( auto str : str_list )
    {
        model->appendRow( new QStandardItem( str ) );
    }
}

FusekiServerSetting::~FusekiServerSetting()
{
    emit stopCommand();
}

void FusekiServerSetting::createWidget()
{
    QPushButton* button_download_java = new QPushButton( "Download Java Installer", this );
    button_start = new QPushButton( "Start Fuseki Server", this );
    QPushButton* button_open_page = new QPushButton( "Open Fuseki Server", this );

    QLabel* link_label = new QLabel( "Dataset Name: ", this );
    link_label->setMaximumHeight( 30 );
    line_edit_link = new QLineEdit( this );
    QLabel* label_prefixs = new QLabel( "Prefixs:", this );

    list_view_prefixs = new QListView( this );
    model = new QStandardItemModel();
    list_view_prefixs->setModel( model );

    QPushButton* button_list_add = new QPushButton( "Add Row", this );
    QPushButton* button_list_remove = new QPushButton( "Remove Row", this );
    QPushButton* button_save_settings = new QPushButton( "Save Settings", this );
    QPushButton* button_close_window = new QPushButton( "Close", this );
    QPushButton* button_test_settings = new QPushButton( "Test Settings", this );

    button_download_java->setMaximumWidth( 500 );
    button_start->setMaximumWidth( 500 );
    button_open_page->setMaximumWidth( 500 );
    link_label->setMaximumWidth( 500 );
    line_edit_link->setMaximumWidth( 500 );
    label_prefixs->setMaximumWidth( 500 );
    label_prefixs->setMaximumHeight( 30 );

    list_view_prefixs->setMaximumWidth( 500 );
    list_view_prefixs->setMinimumHeight( 400 );
    list_view_prefixs->setMaximumHeight( 400 );

    button_list_add->setMaximumWidth( 240 );
    button_list_remove->setMaximumWidth( 240 );
    button_test_settings->setMaximumWidth( 500 );
    button_save_settings->setMaximumWidth( 240 );
    button_close_window->setMaximumWidth( 240 );

    connect( button_download_java, SIGNAL( clicked() ), this, SLOT( downloadJava() ) );
    connect( button_start, SIGNAL( clicked() ), this, SLOT( startFuseki() ) );
    connect( button_open_page, SIGNAL( clicked() ), this, SLOT( openFuseki() ) );
    connect( button_list_add, SIGNAL( clicked() ), this, SLOT( listAdd() ) );
    connect( button_list_remove, SIGNAL( clicked() ), this, SLOT( listRemove() ) );
    connect( button_save_settings, SIGNAL( clicked() ), this, SLOT( saveSettings() ) );
    connect( button_close_window, SIGNAL( clicked() ), this, SLOT( closeWindow() ) );
    connect( button_test_settings, SIGNAL( clicked() ), this, SLOT( testSettings() ) );

    QGridLayout* gridLayout = new QGridLayout( this );
    gridLayout->addWidget( new QLabel( this ), 3, 0, 1, 1 );
    gridLayout->addWidget( new QLabel( this ), 3, 3, 1, 2 );
    gridLayout->addWidget( button_download_java, 4, 3, 1, 2 );
    gridLayout->addWidget( button_start, 5, 3, 1, 2 );
    gridLayout->addWidget( button_open_page, 6, 3, 1, 2 );
    gridLayout->addWidget( link_label, 7, 3, 1, 2 );
    gridLayout->addWidget( line_edit_link, 8, 3, 1, 2 );
    gridLayout->addWidget( label_prefixs, 10, 3, 1, 2 );
    gridLayout->addWidget( list_view_prefixs, 11, 3, 1, 2 );
    gridLayout->addWidget( button_list_add, 12, 3, 1, 1 );
    gridLayout->addWidget( button_list_remove, 12, 4, 1, 1 );
    gridLayout->addWidget( new QLabel( this ), 13, 3, 1, 3 );
    gridLayout->addWidget( new QLabel( this ), 13, 5, 1, 1 );
    gridLayout->addWidget( button_test_settings, 14, 3, 1, 2 );
    gridLayout->addWidget( button_save_settings, 15, 3, 1, 1 );
    gridLayout->addWidget( button_close_window, 15, 4, 1, 1 );
}

void FusekiServerSetting::listAdd()
{
    model->appendRow( new QStandardItem( "PREFIX : <>" ) );
}

void FusekiServerSetting::listRemove()
{
    model->removeRow( list_view_prefixs->currentIndex().row() );
}

void FusekiServerSetting::startFuseki()
{
    if ( flag_started )
    {
        emit stopCommand();
        button_start->setText( "Start Fuseki Server" );
    }
    else
    {
        emit runCommand( QString( FUSEKI_SERVER_PATH ) );
        button_start->setText( "Stop Fuseki Server" );
    }
    flag_started = !flag_started;
}

void FusekiServerSetting::openFuseki()
{
    QDesktopServices::openUrl( QUrl( "http://localhost:3030" ) );
}

void FusekiServerSetting::downloadJava()
{
    QDesktopServices::openUrl( QUrl( "https://drive.google.com/u/0/uc?id=1G1dmRDCt4KDhZaNySOUl6lJqtTf6G3Tl&export=download&confirm=t&uuid=8ed1d411-023f-4456-bed5-6e22f7761fee&at=AKKF8vzTcWqxFKHUZ2X-OtQGN7lX:1683796000413 " ) );
}

void FusekiServerSetting::saveSettings()
{
    master.setSetting( "SPARQL_dataset_name", line_edit_link->text() );
    QStringList str_list;
    for ( int i = 0; i < model->rowCount(); ++i )
    {
        str_list << model->item( i )->text();
    }
    master.setSetting( "SPARQL_prefixs", str_list );
}

void FusekiServerSetting::closeWindow()
{
}

void FusekiServerSetting::testSettings()
{
}
