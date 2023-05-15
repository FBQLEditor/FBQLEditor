#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWebView>

#include <mainwindow.h>
#include <swidget.h>

class MainPage : public SWidget
{
    Q_OBJECT
public:
    virtual SWidgetTypes typeSWidget() { return MainPageType; }
    virtual int modeDiagramBlocks() { return BlocksLibrary::ModeBlocks::None; }

    explicit MainPage( MainWindow* main_window );

    void createForm();
    void makePage();

private:
    QWebView* web;
    MainWindow* main_window;
};

#endif // MAINPAGE_H
