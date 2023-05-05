#include "stoolbar.h"

#include <QToolButton>
#include <diagramscene.h>

SToolBar::SToolBar( SMenuBar& menubar, QWidget* parent )
    : QToolBar( parent )
{
    CreateToolBar( menubar );
}

void SToolBar::CreateToolBar( SMenuBar& menubar )
{
    addAction( menubar.createNewProjectAction );
    addAction( menubar.openProjectAction );
    addAction( menubar.saveProjectAction );

    addSeparator();
    addAction( menubar.createBasedBlockAction );
    addAction( menubar.createCompositeBlockAction );
    addAction( menubar.createSparqlBlockAction );

    addSeparator();
    addAction( menubar.deleteAction );
    addAction( menubar.toFrontAction );
    addAction( menubar.sendBackAction );
    addAction( menubar.reworkBlockAction );
    addAction( menubar.runSceneScriptAction );

    addSeparator();
    addAction( menubar.settingFusekiServer );
}

void SToolBar::setSettings( Settings setting )
{
    auto list_button = pointer_type_group->buttons();
    for ( int i = 0; i < list_button.size(); ++i )
    {
        if ( setting != i )
        {
            list_button.at( i )->setChecked( false );
            continue;
        }
        list_button.at( i )->setChecked( true );
    }
}
