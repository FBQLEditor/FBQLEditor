#ifndef DIAGRAMITEMBASIC_H
#define DIAGRAMITEMBASIC_H

#include <basicblocksettings.h>
#include <diagramitem.h>

#include <QFont>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>

class DiagramItemBasic : public DiagramItem
{
public:
    virtual int type() const override { return BasicItemType; }

    DiagramItemBasic( QMenu* contextMenu, QGraphicsItem* parent = nullptr, BasicBlockSettings* setting = new BasicBlockSettings() );
    void setSettings( BasicBlockSettings* setting );
    QString getName();
    BasicBlockSettings* getSettings() override;
    QString getInputData() override;
    void setDrawPicture( bool );
    QString getScript() override;

private:
    QGraphicsTextItem* name;
    QGraphicsTextItem* label;
    QLineEdit* line_edit;
    QGraphicsProxyWidget* proxy_line_edit;
    QGraphicsProxyWidget* proxy_picture;
    QLabel* picture;
    QPixmap pixmap;
    QString script;
};

#endif // DIAGRAMITEMBASIC_H
