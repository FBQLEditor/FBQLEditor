#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "projectwindow.h"
#include <QDebug>

#include <atomblocksettings.h>
#include <basedblockwindow.h>
#include <compositeblockwindow.h>
#include <diagramexecutor.h>
#include <fusekiserversetting.h>
#include <ioblocksettings.h>
#include <mainpage.h>
#include <sparqlblockwindow.h>

#define APPLICATION_NAME "FBQL Editor"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    QCoreApplication::setApplicationName( APPLICATION_NAME );
    setWindowTitle( QCoreApplication::applicationName() );
    QDir().mkdir( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) );
    QDir().mkdir( QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) + "/" + APPLICATION_NAME );

    library = new BlocksLibrary();
    library->loadBlocksFromFiles( FOLDER_FOR_DEFAULT_BLOCKS );
    library->loadBlocksFromFiles( FOLDER_FOR_USERS_BLOCKS );
    library->addBlocks( AtomBlockSettings::GetBasedAtomBlocks() );
    library->addBlocks( IOBlockSettings::GetBasedIOBlocks() );

    createMainForm();
    slotOnOpenMainPage();

    open_save_processor = new SOpenSaveProcessor( item_menu, this );
    connect( open_save_processor, SIGNAL( widgetCreate( SWidget*, QString ) ), tab_widget, SLOT( addWidget( SWidget*, QString ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMainForm()
{
    menu_bar = new SMenuBar( this );
    setMenuBar( menu_bar );

    QWidget* widget = new QWidget( this );
    main_layout = new QGridLayout( widget );
    widget->setLayout( main_layout );

    tab_widget = new STabWidget( this );
    connect( tab_widget, SIGNAL( newCurrentMode( int ) ),
        this, SLOT( slotCurrentTabMode( int ) ) );

    tool_box = new SToolBox( this );
    connect( tool_box, SIGNAL( itemPressed( DiagramItemSettings* ) ),
        tab_widget, SLOT( itemForAdd( DiagramItemSettings* ) ) );

    tool_bar = new SToolBar( *menu_bar, this );
    addToolBar( Qt::TopToolBarArea, tool_bar );

    main_layout->addWidget( tool_box, 0, 0 );
    main_layout->addWidget( tab_widget, 0, 1 );

    setCentralWidget( widget );
}

void MainWindow::slotOnOpenMainPage()
{
    auto window = new MainPage( this );
    tab_widget->addWidget( window, tr( "Main Page" ) );
}

void MainWindow::slotCreateNewProject()
{
    auto window = new ProjectWindow( item_menu, this );
    tab_widget->addWidget( window, tr( "New Project" ) );
}

void MainWindow::slotCreateBasedBlock()
{
    auto window = new BasedBlockWindow( BasedBlockWindow::CreateMode, tab_widget );
    tab_widget->addWidget( window, tr( "New Block" ) );
}

void MainWindow::slotCreateCompositeBlock()
{
    auto window = new CompositeBlockWindow( item_menu, this );
    tab_widget->addWidget( window, tr( "Composite Block" ) );
    connect( window, SIGNAL( blockCreated( DiagramItemSettings* ) ), this, SLOT( slotOnCreateBlock( DiagramItemSettings* ) ) );
}

void MainWindow::slotCreateSparqlBlock()
{
    auto window = new SparqlBlockWindow( item_menu, this );
    tab_widget->addWidget( window, tr( "New Sparql" ) );
    connect( window, SIGNAL( blockCreated( DiagramItemSettings* ) ), this, SLOT( slotOnCreateBlock( DiagramItemSettings* ) ) );
}

void MainWindow::slotOnCreateBlock( DiagramItemSettings* settings )
{
    library->addBlock( settings );
    tab_widget->resetBlocks();
}

void MainWindow::slotCurrentTabMode( int mode )
{
    tool_box->setDiagramItems( library->getBlocks( mode ) );
}

void MainWindow::slotOnClickedBlockExecutor()
{
    auto list_blocks = tab_widget->getBlocksForRun();
    if ( !list_blocks.empty() )
    {
        auto window = new DiagramExecutor( this );
        window->setDiagramItem( list_blocks );
        tab_widget->addWidget( window, "Exec" );
    }
}

void MainWindow::setItemMenu( QMenu* menu )
{
    item_menu = menu;
}

void MainWindow::slotOnDeleteItemOnScene()
{
    tab_widget->deleteItemOnScene();
}

void MainWindow::slotOnOpenProject()
{
    open_save_processor->openFBAndCreateWidget();
}

void MainWindow::slotOnSaveProject()
{
    tab_widget->saveProject();
}

void MainWindow::slotOnSettingFusekiServer()
{
    auto window = new FusekiServerSetting( this );
    tab_widget->addWidget( window, tr( "Fuseki" ) );
}
