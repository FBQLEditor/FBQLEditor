#include "basicblockwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QPushButton>
#include <QVariant>
#include <exception>

BasicBlockWindow::BasicBlockWindow( const BasicMode& mode, QWidget* parent )
    : SWidget( parent )
{
    setMode( mode );
    createWidget();
    BasicBlockSettings* settings = new BasicBlockSettings();
    setSettings( settings );
    delete settings;
}

void BasicBlockWindow::setMode( const BasicMode& mode )
{
    mode_ = mode;
}

void BasicBlockWindow::setBlockOnRework( DiagramItemBasic* item )
{
    if ( ReworkMode == mode_ )
        emit error( tr( "BasicBlockWindow, this not rework mode!" ) );
    item_on_rework = item;
    setSettings( item->getSettings() );
}

void BasicBlockWindow::setSettings( BasicBlockSettings* settings )
{
    line_name->setText( settings->block_name );
    line_label->setText( settings->label_text );
    line_line_edit->setText( settings->line_edit_text );

    check_label->setChecked( settings->label );
    check_line_edit->setChecked( settings->line_edit );

    text_edit->setText( settings->script );

    if ( settings->pixmap.isNull() )
    {
        settings->pixmap = settings->image().scaled( 70, 70 );
    }
    pixmap = settings->pixmap;
    label_pixmap->setPixmap( settings->pixmap.scaled( 70, 70 ) );
}

void BasicBlockWindow::createWidget()
{
    QGridLayout* gridLayout = new QGridLayout( this );

    QLabel* label_for_label = new QLabel( tr( "Text label:" ), this );
    QLabel* label_for_script = new QLabel( tr( "Script:" ), this );
    QLabel* label_for_name_blocks = new QLabel( tr( "Name Block:" ), this );
    QLabel* label_for_line_edit = new QLabel( tr( "Text lineEdit:" ), this );
    label_pixmap = new QLabel( tr( "NULL" ), this );

    QPushButton* button_info = new QPushButton( tr( "Info" ), this );
    QPushButton* button_save = new QPushButton( tr( "Save" ), this );
    QPushButton* button_open = new QPushButton( tr( "Open" ), this );
    QPushButton* button_test_script = new QPushButton( tr( "Test Script" ), this );
    QPushButton* button_set_image = new QPushButton( tr( "Set Image" ), this );
    QPushButton* button_delete_image = new QPushButton( tr( "Delete Image" ), this );
    connect( button_info, SIGNAL( clicked() ),
        this, SLOT( slotInfo() ) );
    connect( button_save, SIGNAL( clicked() ),
        this, SLOT( slotOnSaveButtonClicked() ) );
    connect( button_open, SIGNAL( clicked() ),
        this, SLOT( slotOnOpenButtonClicked() ) );
    connect( button_test_script, SIGNAL( clicked() ),
        this, SLOT( slotTestScript() ) );
    connect( button_set_image, SIGNAL( clicked() ),
        this, SLOT( slotSetImage() ) );
    connect( button_delete_image, SIGNAL( clicked() ),
        this, SLOT( slotDeleteImage() ) );

    line_name = new QLineEdit( this );
    line_line_edit = new QLineEdit( this );
    line_label = new QLineEdit( this );

    check_line_edit = new QCheckBox( tr( "LineEdit" ), this );
    check_label = new QCheckBox( tr( "Label" ), this );

    text_edit = new QTextEdit( this );
    text_edit->setTabStopWidth( 30 );

    gridLayout->addWidget( label_for_label, 4, 2, 1, 1 );
    gridLayout->addWidget( label_for_script, 6, 1, 1, 1 );
    gridLayout->addWidget( label_for_name_blocks, 1, 1, 1, 1 );
    gridLayout->addWidget( label_for_line_edit, 4, 4, 1, 1 );
    gridLayout->addWidget( label_pixmap, 0, 4, 3, 1 );

    gridLayout->addWidget( button_info, 6, 3, 1, 1 );
    gridLayout->addWidget( button_save, 8, 4, 1, 1 );
    gridLayout->addWidget( button_open, 8, 3, 1, 1 );
    gridLayout->addWidget( button_test_script, 6, 4, 1, 1 );
    gridLayout->addWidget( button_set_image, 1, 3, 1, 1 );
    gridLayout->addWidget( button_delete_image, 2, 3, 1, 1 );

    gridLayout->addWidget( line_name, 2, 1, 1, 2 );
    gridLayout->addWidget( line_line_edit, 5, 3, 1, 2 );
    gridLayout->addWidget( line_label, 5, 1, 1, 2 );

    gridLayout->addWidget( check_line_edit, 4, 3, 1, 1 );
    gridLayout->addWidget( check_label, 4, 1, 1, 1 );
    gridLayout->addWidget( text_edit, 7, 1, 1, 4 );
}

void BasicBlockWindow::slotInfo()
{
}

void BasicBlockWindow::slotOnSaveButtonClicked()
{
    QJsonDocument json;
    BasicBlockSettings* settings = getSettings();
    json.setObject( settings->getJsonFromSetting() );
    saveFile( json.toJson(), DiagramItemSettings::getFileFormat( DiagramItemSettings::BlockFileFormat ) );
    emit blockCreated( settings );
}

void BasicBlockWindow::slotOnOpenButtonClicked()
{
    BasicBlockSettings* settings = new BasicBlockSettings();
    settings->setSettingFromString( openFile( DiagramItemSettings::getFileFormat( DiagramItemSettings::BlockFileFormat ) ) );
    setSettings( settings );
    delete settings;
}

void BasicBlockWindow::slotTestScript()
{
}

void BasicBlockWindow::slotSetImage()
{
}

void BasicBlockWindow::slotDeleteImage()
{
}

void BasicBlockWindow::slotSetName( const QString& name )
{
    emit changeNameWindow( name );
}

BasicBlockSettings* BasicBlockWindow::getSettings()
{
    BasicBlockSettings* settings = new BasicBlockSettings();
    settings->block_name = line_name->text();
    settings->label = check_label->isChecked();
    settings->line_edit = check_line_edit->isChecked();
    settings->label_text = line_label->text();
    settings->line_edit_text = line_line_edit->text();
    settings->script = text_edit->toPlainText();
    settings->pixmap = pixmap;
    return settings;
}

QString BasicBlockWindow::getName( const QString& path )
{
    QStringList lst = path.split( "/" );
    return lst.at( lst.size() - 1 );
}
