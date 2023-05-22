#include "swidget.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

SWidget::SWidget( QWidget* parent )
    : QWidget( parent )
{
}

QString SWidget::openFile( const QString& format )
{
    QString file_name = QFileDialog::getOpenFileName( this, "Choose File", QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) + "/FBQL Editor/", format.toUpper() + " (*." + format + ");;JSON (*.json)" );
    QFile file( file_name );
    QString result;
    if ( file.open( QIODevice::ReadOnly ) )
    {
        result = file.readAll();
        emit setTabName( QFileInfo( file.fileName() ).fileName() );
        //  QMessageBox::about( this, tr( "Basic Block" ), tr( "Block is open!" ) );
    }
    else
    {
        QMessageBox::about( this, tr( "Basic Block" ), tr( "Failed open block!" ) );
    }
    file.close();
    return result;
}

void SWidget::saveFile( const QString& text, const QString& format )
{
    auto file_name = QFileDialog::getSaveFileName( this, "Save as", QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) + "/FBQL Editor/", format.toUpper() + " (*." + format + ")" );
    auto list = file_name.split( "." );
    if ( list.size() == 1 || list.back() != format )
    {
        file_name += "." + format;
    }

    QFile file( file_name );
    if ( file.open( QIODevice::WriteOnly ) )
    {
        file.write( text.toLatin1() );
        // QMessageBox::about( this, tr( "Basic Block" ), tr( "Block is saved!" ) );
    }
    else
    {
        QMessageBox::about( this, tr( "Basic Block" ), tr( "Failed save block!" ) );
    }
    file.close();
}
