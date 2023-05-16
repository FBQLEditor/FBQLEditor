#include "sopensaveprocessor.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include <basedblockwindow.h>
#include <compositeblockwindow.h>
#include <projectwindow.h>
#include <sparqlblockwindow.h>

SOpenSaveProcessor::SOpenSaveProcessor( QMenu* context_menu, QWidget* parent )
    : QObject( parent )
    , my_parent( parent )
    , context_menu( context_menu )
{
    folder_default = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
    folder_users = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) + "/FBQL Editor/";
}

void SOpenSaveProcessor::openFBAndCreateWidget()
{
    auto files_name = QFileDialog::getOpenFileNames( my_parent, "Open Files", folder_users, "*.fbd *.fbql *.json" );

    for ( auto file_name : files_name )
    {
        QFile file( file_name );
        if ( file.open( QIODevice::ReadOnly ) )
        {
            auto short_name = QFileInfo( file_name ).fileName();
            auto json = QJsonDocument::fromJson( file.readAll() );
            if ( json.isObject() )
            {
                auto object = json.object();
                if ( BasedBlockSettings::CheckSettings( object ) )
                {
                    auto widget = new BasedBlockWindow( BasedBlockWindow::CreateMode, my_parent );
                    auto settings = new BasedBlockSettings();
                    settings->setSettingFromJson( object );
                    widget->setSettings( settings );
                    emit widgetCreate( widget, short_name );
                }
                else if ( CompositeBlockSettings::CheckSettings( object ) )
                {
                    auto widget = new CompositeBlockWindow( context_menu, my_parent );
                    auto settings = new CompositeBlockSettings();
                    settings->setSettingFromJson( object );
                    widget->setSettings( settings );
                    emit widgetCreate( widget, short_name );
                }
                else if ( SparqlBlockSettings::CheckSettings( object ) )
                {
                    auto widget = new SparqlBlockWindow( context_menu, my_parent );
                    auto settings = new SparqlBlockSettings();
                    settings->setSettingFromJson( object );
                    widget->setSettings( settings );
                    emit widgetCreate( widget, short_name );
                }
                else if ( ProjectWindowSettings::CheckSettings( object ) )
                {
                    auto widget = new ProjectWindow( context_menu, my_parent );
                    auto settings = new ProjectWindowSettings();
                    settings->setSettingFromJson( object );
                    // widget->setSettings( settings );
                    emit widgetCreate( widget, short_name );
                }
            }
        }
    }
}
