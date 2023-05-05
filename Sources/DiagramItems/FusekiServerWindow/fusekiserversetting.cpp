#include "fusekiserversetting.h"

#include <QDesktopServices>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#ifdef Q_OS_LINUX
#define FUSEKI_SERVER_PATH "FusekiServer/fuseki-server"
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
}

FusekiServerSetting::~FusekiServerSetting()
{
    emit stopCommand();
}

void FusekiServerSetting::createWidget()
{
    button_start = new QPushButton( "Start Fuseki Server", this );
    button_start->setMaximumWidth( 500 );
    QPushButton* button_open_page = new QPushButton( "Open Fuseki Server", this );
    button_open_page->setMaximumWidth( 500 );
    QLabel* link_label = new QLabel( "Links: ", this );
    link_label->setMaximumWidth( 500 );
    link_label->setMaximumHeight( 30 );
    line_edit_link = new QLineEdit( this );
    line_edit_link->setMaximumWidth( 500 );
    QPushButton* button_set_link = new QPushButton( "Set Links" );

    QLabel* label_prefixs = new QLabel( "Prefixs:", this );
    label_prefixs->setMaximumHeight( 30 );

    list_view_prefixs = new QListView( this );
    list_view_prefixs->setMaximumWidth( 500 );
    list_view_prefixs->setMinimumHeight( 400 );
    list_view_prefixs->setMaximumHeight( 400 );

    model = new QStandardItemModel( list_view_prefixs );
    list_view_prefixs->setModel( model );

    QPushButton* button_list_add = new QPushButton( "Add Row", this );
    QPushButton* button_list_remove = new QPushButton( "Remove Row", this );

    connect( button_start, SIGNAL( clicked() ), this, SLOT( startFuseki() ) );
    connect( button_open_page, SIGNAL( clicked() ), this, SLOT( openFuseki() ) );
    connect( button_set_link, SIGNAL( clicked() ), this, SLOT( setLinkPage() ) );
    connect( button_list_add, SIGNAL( clicked() ), this, SLOT( listAdd() ) );
    connect( button_list_remove, SIGNAL( clicked() ), this, SLOT( listRemove() ) );

    QGridLayout* gridLayout = new QGridLayout( this );
    gridLayout->addWidget( new QLabel( this ), 0, 0, 1, 1 );
    gridLayout->addWidget( button_start, 1, 0, 1, 1 );
    gridLayout->addWidget( button_open_page, 2, 0, 1, 1 );
    gridLayout->addWidget( link_label, 3, 0, 1, 1 );
    gridLayout->addWidget( line_edit_link, 4, 0, 1, 1 );
    gridLayout->addWidget( button_set_link, 5, 0, 1, 1 );
    gridLayout->addWidget( label_prefixs, 6, 0, 1, 1 );
    gridLayout->addWidget( list_view_prefixs, 7, 0, 1, 1 );
    gridLayout->addWidget( button_list_add, 8, 0, 1, 1 );
    gridLayout->addWidget( button_list_remove, 9, 0, 1, 1 );
    gridLayout->addWidget( new QLabel( this ), 10, 0, 1, 1 );
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
        emit runCommand( QString( "./%1" ).arg( FUSEKI_SERVER_PATH ) );
        button_start->setText( "Stop Fuseki Server" );
    }
    flag_started = !flag_started;
}

void FusekiServerSetting::testConnectToPage()
{
}

void FusekiServerSetting::setLinkPage()
{
    MainSettings::setSetting( "SPARQL_link", line_edit_link->text() );
}

void FusekiServerSetting::openFuseki()
{
    QDesktopServices::openUrl( QUrl( "http://localhost:3030" ) );
}

void FusekiServerSetting::testStart()
{
}
