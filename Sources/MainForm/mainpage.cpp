#include "mainpage.h"

#include <QGridLayout>
#include <QPushButton>
#include <QWebFrame>

MainPage::MainPage( MainWindow* main_window )
    : SWidget( main_window )
    , main_window( main_window )
{
    createForm();
    makePage();
}

void MainPage::createForm()
{
    QGridLayout* grid_layout = new QGridLayout( this );
    setLayout( grid_layout );

    QPushButton* button_back = new QPushButton( "<< Back <<", this );

    web = new QWebView( this );
    web->page()->mainFrame()->addToJavaScriptWindowObject( "MainWindow", main_window );

    connect( button_back, SIGNAL( clicked() ), web, SLOT( back() ) );

    grid_layout->addWidget( button_back );
    grid_layout->addWidget( web );
}

void MainPage::makePage()
{
    web->load( QUrl( "qrc:///Sources/html/main_page.html" ) );
}
