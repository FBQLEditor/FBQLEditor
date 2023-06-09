#include "sparqlblockwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QMessageBox>
#include <QPushButton>

#include <diagramarrow.h>

SparqlBlockWindow::SparqlBlockWindow( QMenu* context_menu, QWidget* parent )
    : SGraphicsView( context_menu, parent )
{
    createSidePanel();
    setSettings( SparqlBlockSettings::CreateTemplateSparqlSettings() );

    query_edit = new QTextEdit( this );
    query_edit->setReadOnly( true );
    getStackedWidget()->insertWidget( getStackedWidget()->count(), query_edit );
}

QWidget* SparqlBlockWindow::addCustomWidget()
{
    QWidget* widget = new QWidget( this );
    QGridLayout* grid_layout = new QGridLayout();
    widget->setLayout( grid_layout );

    QLabel* label_name = new QLabel( "Name block:", this );
    label_name->setMaximumHeight( 30 );
    line_name_block = new QLineEdit( this );
    line_name_block->setText( "Sparql" );

    QLabel* label_limit = new QLabel( "Limit:", this );
    label_limit->setMaximumHeight( 30 );
    spin_box_limit = new QSpinBox( this );
    spin_box_limit->setMaximum( 1000 );
    spin_box_limit->setMinimum( 0 );
    spin_box_limit->setValue( 20 );

    box_query = new QCheckBox( "Use text instead\n of a diagram", this );

    connect( box_query, SIGNAL( stateChanged( int ) ), this, SLOT( slotClickCheckBoxQuery() ) );

    grid_layout->addWidget( label_name, 0, 0 );
    grid_layout->addWidget( line_name_block, 1, 0 );
    grid_layout->addWidget( label_limit, 2, 0 );
    grid_layout->addWidget( spin_box_limit, 3, 0 );
    grid_layout->addWidget( box_query, 4, 0 );
    widget->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum ) );

    return widget;
}

QWidget* SparqlBlockWindow::addCustomBotWidget()
{
    QWidget* widget = new QWidget( this );
    QGridLayout* grid_layout = new QGridLayout();
    widget->setLayout( grid_layout );

    // QPushButton* button_create_block = new QPushButton( "Create", this );
    // connect( button_create_block, SIGNAL( clicked() ), this, SLOT( slotOnCreateButtonClicked() ) );

    QPushButton* button_save_block = new QPushButton( "Save", this );
    connect( button_save_block, SIGNAL( clicked() ), this, SLOT( slotOnSaveButtonClicked() ) );

    QPushButton* button_open_block = new QPushButton( "Open", this );
    connect( button_open_block, SIGNAL( clicked() ), this, SLOT( slotOnOpenButtonClicked() ) );

    QPushButton* button_write_query = new QPushButton( "Query", this );
    connect( button_write_query, SIGNAL( clicked() ), this, SLOT( slotOpenQuery() ) );

    grid_layout->addWidget( button_write_query, 0, 0 );
    // grid_layout->addWidget( button_create_block, 1, 0 );
    grid_layout->addWidget( button_save_block, 2, 0 );
    grid_layout->addWidget( button_open_block, 3, 0 );

    return widget;
}

void SparqlBlockWindow::slotClickCheckBoxQuery()
{
    query_edit->setReadOnly( !box_query->isChecked() );
}

void SparqlBlockWindow::slotOpenQuery()
{
    if ( getStackedWidget()->currentIndex() == 0 )
    {
        if ( !box_query->isChecked() )
        {
            auto settings = getSettings();
            query_edit->setText( settings->getQuery() );
            delete settings;
        }
        getStackedWidget()->setCurrentWidget( query_edit );
    }
    else
    {
        getStackedWidget()->setCurrentIndex( 0 );
    }
}

// void SparqlBlockWindow::slotOnCreateButtonClicked()
//{
//     emit blockCreated( getSettings() );
// }

void SparqlBlockWindow::slotOnSaveButtonClicked()
{
    /*QMessageBox msgBox;
    msgBox.setMinimumWidth( 400 );
    msgBox.setText( "What should be taken as the basis of the request?" );
    msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
    msgBox.button( QMessageBox::Yes )->setIcon( QIcon() );
    msgBox.button( QMessageBox::No )->setIcon( QIcon() );
    msgBox.button( QMessageBox::Yes )->setText( "Text request" );
    msgBox.button( QMessageBox::No )->setText( "Diagram" );
    msgBox.setDefaultButton( QMessageBox::No );
    int result = msgBox.exec();

    if ( QMessageBox::Yes == result )
    {
    }*/

    auto settings = getSettings();
    QJsonDocument json;
    json.setObject( settings->getJsonFromSetting() );
    saveFile( json.toJson(), DiagramItemSettings::getFileFormat( DiagramItemSettings::BlockFileFormat ) );
    emit blockCreated( settings );
}

void SparqlBlockWindow::slotOnOpenButtonClicked()
{
    SparqlBlockSettings* settings = new SparqlBlockSettings();
    settings->setSettingFromString( openFile( DiagramItemSettings::getFileFormat( DiagramItemSettings::BlockFileFormat ) ) );
    setSettings( settings );
}

void SparqlBlockWindow::setSettings( SparqlBlockSettings* settings )
{
    spin_box_limit->setValue( settings->limit );
    line_name_block->setText( settings->block_name );

    if ( settings->use_query )
    {
        box_query->setChecked( true );
        query_edit->setText( settings->query );
        slotOpenQuery();
        return;
    }

    getScene()->clear();

    QVector<DiagramItemAtom*> areas_items;
    for ( const auto& area : settings->areas )
    {
        DiagramItemAtom* area_item = new DiagramItemAtom( nullptr, nullptr, area.settings );
        getScene()->addItem( area_item );
        areas_items.push_back( area_item );

        QVector<DiagramItem*> blocks;
        for ( const auto& block : area.blocks )
        {
            DiagramItemAtom* item = new DiagramItemAtom( nullptr, area_item, block );
            blocks.push_back( item );
        }

        for ( const auto& line : area.lines )
        {
            auto arrow = getScene()->createArrow( blocks.at( line.start_block ), blocks.at( line.end_block ) );
            if ( line.text != "" )
                arrow->setText( line.text );
        }
    }

    for ( const auto& line : settings->lines )
    {
        auto arrow = getScene()->createArrow( areas_items.at( line.start_block ), areas_items.at( line.end_block ) );
        if ( line.text != "" )
            arrow->setText( line.text );
    }

    delete settings;
}

SparqlBlockSettings* SparqlBlockWindow::getSettings()
{
    SparqlBlockSettings* settings = new SparqlBlockSettings();
    settings->block_name = line_name_block->text();
    settings->limit = spin_box_limit->value();
    if ( box_query->isChecked() )
    {
        settings->use_query = true;
        settings->query = query_edit->toPlainText();
        return settings;
    }

    QMap<DiagramItemAtom*, QVector<DiagramItemAtom*>> blocks_area;
    DiagramItemAtom* start_area;
    auto full_items = getScene()->items();

    // check areas
    for ( QGraphicsItem* item : full_items )
    {
        if ( DiagramItem::AtomItemType == item->type() )
        {
            auto atom_item = static_cast<DiagramItemAtom*>( item );
            if ( DEFAULT_AREA == atom_item->getSettings()->type_block )
            {
                blocks_area.insert( atom_item, {} );
            }
        }
    }

    // check blocks
    for ( QGraphicsItem* item : full_items )
    {
        if ( DiagramItem::AtomItemType == item->type() )
        {
            auto atom_item = static_cast<DiagramItemAtom*>( item );
            if ( ( DEFAULT_VAR == atom_item->getSettings()->type_block
                     || DEFAULT_VALUE == atom_item->getSettings()->type_block )
                && nullptr != atom_item->parentItem()
                && DiagramItem::AtomItemType == atom_item->parentItem()->type() )
            {
                auto parent_item = static_cast<DiagramItemAtom*>( atom_item->parentItem() );
                blocks_area[parent_item].push_back( atom_item );
            }
        }
    }

    // find start
    bool flag_find = false;
    for ( auto& area : blocks_area.keys() )
    {
        auto arrows = area->getEndArrows();
        if ( 0 == arrows.size() )
        {
            if ( flag_find )
            {
                emit ERROR( "Sparql wrong format! Find > 1 start area!" );
                return {};
            }
            else
            {
                start_area = area;
                flag_find = true;
            }
        }
    }

    // generatesettings
    auto area_list = blocks_area.keys();
    for ( auto& area : area_list )
    {
        SparqlBlockSettings::AreaSaver area_saver;
        area_saver.settings = area->getSettings();

        // blocks
        auto blocks_item = blocks_area[area];
        for ( auto& item : blocks_item )
        {
            area_saver.blocks.push_back( item->getSettings() );
            auto arrows = item->getStartArrows();
            for ( auto& arrow : arrows )
            {
                SparqlBlockSettings::LineSaver line_saver;
                line_saver.text = arrow->getText();
                line_saver.start_block = blocks_item.indexOf( item );
                if ( DiagramItem::AtomItemType == arrow->endItem()->type() )
                {
                    line_saver.end_block = blocks_item.indexOf( static_cast<DiagramItemAtom*>( arrow->endItem() ) );
                }
                else
                {
                    emit ERROR( "Sparql wrong format! Unknown type blocks!" );
                }
                area_saver.lines.push_back( line_saver );
            }
        }

        settings->areas.push_back( area_saver );
        auto arrows = area->getStartArrows();
        for ( auto& arrow : arrows )
        {
            SparqlBlockSettings::LineSaver line_saver;
            line_saver.text = arrow->getText();
            line_saver.start_block = area_list.indexOf( area );
            if ( DiagramItem::AtomItemType == arrow->endItem()->type() )
            {
                line_saver.end_block = area_list.indexOf( static_cast<DiagramItemAtom*>( arrow->endItem() ) );
            }
            else
            {
                emit ERROR( "Sparql wrong format! Unknown type blocks!" );
            }
            settings->lines.push_back( line_saver );
        }
    }

    settings->start_area = area_list.indexOf( start_area );
    return settings;
}

void SparqlBlockWindow::createDefaultcScene()
{
    clearScene();
    auto atom_list = AtomBlockSettings::GetBasicAtomBlocks();
}

void SparqlBlockWindow::clearScene()
{
    getScene()->clear();
}

bool SparqlBlockWindow::CheckCollisionArea( DiagramItemAtom* item, DiagramItemAtom* area )
{
    QPointF item_pos = item->pos();
    if ( item_pos.x() > area->pos().x() + area->getStartPos().x()
        && item_pos.x() < area->pos().x() + area->getEndPos().x()
        && item_pos.y() > area->pos().y() + area->getStartPos().y()
        && item_pos.y() < area->pos().y() + area->getEndPos().y() )
    {
        return true;
    }
    return false;
}
