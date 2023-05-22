#include "smenubar.h"

SMenuBar::SMenuBar( QWidget* parent )
    : QMenuBar( parent )
{
    CreateActions();
    CreateMenus();
}

void SMenuBar::CreateActions()
{
    connect( this, SIGNAL( createItemMenu( QMenu* ) ),
        parent(), SLOT( setItemMenu( QMenu* ) ) );

    main_page = new QAction( QIcon( ":/Sources/images/icon.png" ), tr( "Main page" ), this );
    main_page->setShortcut( tr( "Ctrl+M" ) );
    main_page->setStatusTip( tr( "Open Main Page" ) );
    connect( main_page, SIGNAL( triggered() ),
        parent(), SLOT( slotOnOpenMainPage() ) );

    toFrontAction = new QAction( QIcon( ":/Sources/images/bringtofront.png" ),
        tr( "Bring to &Front" ), this );
    toFrontAction->setShortcut( tr( "Ctrl+F" ) );
    toFrontAction->setStatusTip( tr( "Bring item to front" ) );
    // connect( toFrontAction, SIGNAL( triggered() ),
    //          parent(), SLOT( bringToFront() ) );

    sendBackAction = new QAction( QIcon( ":/Sources/images/sendtoback.png" ), tr( "Send to &Back" ), this );
    sendBackAction->setShortcut( tr( "Ctrl+T" ) );
    sendBackAction->setStatusTip( tr( "Send item to back" ) );
    // connect( sendBackAction, SIGNAL( triggered() ),
    //          parent(), SLOT( sendToBack() ) );

    reworkBlockAction = new QAction( QIcon( ":/Sources/images/repair.png" ), tr( "Rework Block" ) );
    reworkBlockAction->setShortcut( tr( "Ctrl+A" ) );
    reworkBlockAction->setStatusTip( tr( "Rework Block" ) );
    // connect( reworkBlockAction, SIGNAL( triggered() ),
    //          parent(), SLOT(slotReworkBlock()));

    createNewProjectAction = new QAction( QIcon( ":/Sources/images/new.png" ), tr( "New project" ), this );
    createNewProjectAction->setShortcut( tr( "Ctrl+N" ) );
    createNewProjectAction->setStatusTip( tr( "Create New Project" ) );
    connect( createNewProjectAction, SIGNAL( triggered() ),
        parent(), SLOT( slotCreateNewProject() ) );

    openAction = new QAction( QIcon( ":/Sources/images/open.png" ), tr( "Open" ), this );
    openAction->setShortcut( tr( "Ctrl+O" ) );
    openAction->setStatusTip( tr( "Open Project" ) );
    connect( openAction, SIGNAL( triggered() ),
        parent(), SLOT( slotOnOpen() ) );

    saveAction = new QAction( QIcon( ":/Sources/images/save.png" ), tr( "Save" ), this );
    saveAction->setShortcut( tr( "Ctrl+S" ) );
    saveAction->setStatusTip( tr( "Save Project" ) );
    connect( saveAction, SIGNAL( triggered() ),
        parent(), SLOT( slotOnSave() ) );

    createBasicBlockAction = new QAction( QIcon( ":/Sources/images/basic.png" ), tr( "Basic" ), this );
    createBasicBlockAction->setShortcut( tr( "Ctrl+Q" ) );
    createBasicBlockAction->setStatusTip( tr( "New BasicBlock" ) );
    connect( createBasicBlockAction, SIGNAL( triggered() ),
        parent(), SLOT( slotCreateBasicBlock() ) );

    createCompositeBlockAction = new QAction( QIcon( ":/Sources/images/composite.png" ), tr( "Composite" ), this );
    createCompositeBlockAction->setShortcut( tr( "Ctrl+W" ) );
    createCompositeBlockAction->setStatusTip( tr( "New CompositeBlock" ) );
    connect( createCompositeBlockAction, SIGNAL( triggered() ),
        parent(), SLOT( slotCreateCompositeBlock() ) );

    createSparqlBlockAction = new QAction( QIcon( ":/Sources/images/SPARQL.png" ), tr( "SPARQL" ), this );
    createSparqlBlockAction->setShortcut( tr( "Ctrl+L" ) );
    createSparqlBlockAction->setStatusTip( tr( "New SPARQL Block" ) );
    connect( createSparqlBlockAction, SIGNAL( triggered() ),
        parent(), SLOT( slotCreateSparqlBlock() ) );

    runSceneScriptAction = new QAction( QIcon( ":/Sources/images/execution.png" ), tr( "Run" ), this );
    runSceneScriptAction->setShortcut( tr( "Ctrl+R" ) );
    runSceneScriptAction->setStatusTip( tr( "Run" ) );
    connect( runSceneScriptAction, SIGNAL( triggered() ),
        parent(), SLOT( slotOnClickedBlockExecutor() ) );

    settingFusekiServer = new QAction( QIcon( ":/Sources/images/favicon.png" ), tr( "FusekiServer" ), this );
    settingFusekiServer->setShortcut( tr( "Ctrl+F" ) );
    settingFusekiServer->setStatusTip( tr( "Setting Fuseki Server" ) );
    connect( settingFusekiServer, SIGNAL( triggered() ),
        parent(), SLOT( slotOnSettingFusekiServer() ) );

    deleteAction
        = new QAction( QIcon( ":/Sources/images/delete.png" ), tr( "&Delete" ), this );
    deleteAction->setShortcut( tr( "Delete" ) );
    deleteAction->setStatusTip( tr( "Delete item from diagram" ) );
    connect( deleteAction, SIGNAL( triggered() ),
        parent(), SLOT( slotOnDeleteItemOnScene() ) );

    exitAction = new QAction( tr( "E&xit" ), this );
    exitAction->setShortcuts( QKeySequence::Quit );
    exitAction->setStatusTip( tr( "Quit Scenediagram example" ) );
    // connect( exitAction, SIGNAL( triggered() ),
    //          parent(), SLOT( close() ) );

    aboutAction = new QAction( tr( "A&bout" ), this );
    aboutAction->setShortcut( tr( "F1" ) );
    // connect( aboutAction, SIGNAL( triggered() ),
    //          parent(), SLOT( about() ) );
}

void SMenuBar::CreateMenus()
{
    fileMenu = addMenu( tr( "&File" ) );
    fileMenu->addAction( createNewProjectAction );
    fileMenu->addAction( openAction );
    fileMenu->addAction( saveAction );
    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );

    newItemMenu = addMenu( tr( "&Blocks" ) );
    newItemMenu->addAction( createBasicBlockAction );
    newItemMenu->addAction( createCompositeBlockAction );
    newItemMenu->addAction( createSparqlBlockAction );

    itemMenu = addMenu( tr( "&Item" ) );
    itemMenu->addAction( deleteAction );
    itemMenu->addSeparator();
    itemMenu->addAction( toFrontAction );
    itemMenu->addAction( sendBackAction );
    itemMenu->addSeparator();
    itemMenu->addAction( reworkBlockAction );
    itemMenu->addAction( runSceneScriptAction );
    emit createItemMenu( itemMenu );

    aboutMenu = addMenu( tr( "&Help" ) );
    aboutMenu->addAction( aboutAction );
}
