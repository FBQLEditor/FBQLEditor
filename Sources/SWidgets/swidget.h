#ifndef SWIDGET_H
#define SWIDGET_H

#include <QWidget>

#include <blockslibrary.h>

class SWidget : public QWidget
{
    Q_OBJECT
public:
    enum SWidgetTypes
    {
        SWidgetType,
        SGraphicsViewType,
        BasedBlockWindowType,
        FusekiServerWindowType,
        MainPageType
    };
    virtual SWidgetTypes typeSWidget() { return SWidgetType; }
    virtual int modeDiagramBlocks() { return BlocksLibrary::ModeBlocks::None; }
    virtual void saveProject() {}
    virtual void openProject() {}

    virtual QString openFile( const QString& filter );
    virtual void saveFile( const QString& text, const QString& filter );

    explicit SWidget( QWidget* parent = nullptr );

signals:
    void setTabName( QString );
    void signalCloseWidget();
    void ERROR( QString );
};

#endif // SWIDGET_H
