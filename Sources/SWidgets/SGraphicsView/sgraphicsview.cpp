#include "sgraphicsview.h"

#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

SGraphicsView::SGraphicsView( QMenu* context_menu, QWidget* parent )
    : SWidget( parent )
    , context_menu( context_menu )
{
    setAttribute( Qt::WA_DeleteOnClose );
    createDiagramView();
}

void SGraphicsView::createDiagramView()
{
    grid_layout = new QGridLayout( this );
    setLayout( grid_layout );

    graphics_view = new QGraphicsView( this );
    group_box = new QGroupBox( this );
    group_box->setMaximumWidth( 220 );

    stacked_widget = new QStackedWidget( this );
    stacked_widget->insertWidget( stacked_widget->count(), graphics_view );

    grid_layout->addWidget( stacked_widget, 0, 0 );
    grid_layout->addWidget( group_box, 0, 1 );

    setDiagramScene( createDiagramScene() );
}

QStackedWidget* SGraphicsView::getStackedWidget()
{
    return stacked_widget;
}

void SGraphicsView::setDiagramScene( DiagramScene* scene )
{
    diagram_scene = scene;
    scene->addRect( 0, 0, width_scene, heigth_scene );
    graphics_view->setScene( diagram_scene );
}

DiagramScene* SGraphicsView::createDiagramScene()
{
    auto scene = new DiagramScene( graphics_view );
    scene->setContextMenu( context_menu );
    return scene;
}

void SGraphicsView::createSidePanel()
{
    QLabel* label = new QLabel( "Pos", group_box );

    x_spin_box = new QSpinBox( group_box );
    x_spin_box->setMaximum( width_scene );
    x_spin_box->setMinimum( 0 );
    connect( x_spin_box, SIGNAL( valueChanged( int ) ),
        this, SLOT( updatePosItems() ) );

    y_spin_box = new QSpinBox( group_box );
    y_spin_box->setMaximum( width_scene );
    y_spin_box->setMinimum( 0 );
    connect( y_spin_box, SIGNAL( valueChanged( int ) ),
        this, SLOT( updatePosItems() ) );

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget( label );
    layout->addWidget( x_spin_box );
    layout->addWidget( y_spin_box );

    group_box_layout = new QVBoxLayout( group_box );
    group_box_layout->addLayout( layout, 0 );
    group_box_layout->addWidget( addCustomWidget(), 1 );
    group_box_layout->addSpacerItem( new QSpacerItem( 0, 3000, QSizePolicy::Ignored, QSizePolicy::Ignored ) );
    group_box_layout->addWidget( addCustomBotWidget() );

    group_box->setLayout( group_box_layout );
}

void SGraphicsView::updatePosData()
{
}

void SGraphicsView::updatePosItems()
{
}

DiagramScene* SGraphicsView::getScene()
{
    return diagram_scene;
}

void SGraphicsView::setItemForScene( DiagramItemSettings* settings )
{
    getScene()->setMode( DiagramScene::InsertItem );
    getScene()->setDiagramItemForInserted( settings );
}

void SGraphicsView::setSceneMode( int mode )
{
    getScene()->setMode( static_cast<DiagramScene::SceneMode>( mode ) );
}

void SGraphicsView::removeSelectedGraphicsItems()
{
    getScene()->removeSelectedItems();
}
