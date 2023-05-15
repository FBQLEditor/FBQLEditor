#include "mainpage.h"

#include <QGridLayout>
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

    web = new QWebView( this );
    web->page()->mainFrame()->addToJavaScriptWindowObject( "MainWindow", main_window );

    grid_layout->addWidget( web );
}

void MainPage::makePage()
{
    QFile file( ":/Sources/html/main_page.html" );
    if ( file.open( QIODevice::ReadOnly ) )
    {
        web->setHtml( file.readAll() );
    }
    else
    {
        web->setHtml( "Error load main_page.html" );
    }
    file.close();
}
