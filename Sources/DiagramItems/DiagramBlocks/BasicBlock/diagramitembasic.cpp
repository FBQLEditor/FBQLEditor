#include "diagramitembasic.h"

DiagramItemBasic::DiagramItemBasic( QMenu* contextMenu, QGraphicsItem* parent, BasicBlockSettings* setting )
    : DiagramItem( contextMenu, parent )
{
    setBrush( Qt::yellow );

    name = new QGraphicsTextItem( this );
    label = new QGraphicsTextItem( this );

    proxy_line_edit = new QGraphicsProxyWidget( this );
    proxy_picture = new QGraphicsProxyWidget( this );

    line_edit = new QLineEdit();
    QRect rect( getStartPos().x() + 4, getEndPos().y() - 30,
        getEndPos().x() - getStartPos().x() - 8, 25 );
    line_edit->setGeometry( rect );
    line_edit->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
    line_edit->setStyleSheet( "font-size: 12px; color: blue;" );

    proxy_line_edit->setWidget( line_edit );

    name->setPos( getStartPos() );
    label->setPos( getStartPos().x(), getEndPos().y() - 50 );

    picture = new QLabel();
    picture->setGeometry( getEndPos().x() - 32, getStartPos().y() + 2, 30, 30 );
    proxy_picture->setWidget( picture );

    setSettings( setting );
}

void DiagramItemBasic::setSettings( BasicBlockSettings* setting )
{
    name->setHtml( "<span style=\"font-size: 15px; text-decoration: underline;\">" + setting->block_name + "</span>" );
    if ( setting->label )
    {
        label->setHtml( "<span style=\"font-size: 12px;\">" + setting->label_text + "</span>" );
    }
    else
    {
        label->hide();
    }

    if ( setting->line_edit )
    {
        line_edit->setText( setting->line_edit_text );
    }
    else
    {
        line_edit->hide();
    }
    pixmap = setting->pixmap;
    script = setting->script;
    picture->setPixmap( setting->pixmap.scaled( 30, 30 ) );
}

QString DiagramItemBasic::getName()
{
    return name->toPlainText();
}

QString DiagramItemBasic::getScript()
{
    return script;
}

BasicBlockSettings* DiagramItemBasic::getSettings()
{
    BasicBlockSettings* settings = new BasicBlockSettings();
    settings->block_name = getName();
    settings->label = label->isActive();
    settings->label_text = label->toPlainText();
    settings->line_edit = !line_edit->isHidden();
    settings->line_edit_text = line_edit->text();
    settings->pixmap = pixmap;
    settings->pos = pos();
    settings->script = script;
    return settings;
}

QString DiagramItemBasic::getInputData()
{
    return line_edit->text();
}

void DiagramItemBasic::setDrawPicture( bool flag )
{
    picture->setVisible( flag );
}
