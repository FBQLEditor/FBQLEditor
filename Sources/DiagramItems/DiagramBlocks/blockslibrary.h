#ifndef BLOCKSLIBRARY_H
#define BLOCKSLIBRARY_H

#include <QMap>
#include <QString>
#include <QVector>

#include <diagramitemsettings.h>

#ifdef QT_DEBUG
#define FOLDER_FOR_BLOCKS "../Blocks/"
#else
#define FOLDER_FOR_BLOCKS QStandardPaths::writableLocation( QStandardPaths::AppDataLocation )
#endif

class BlocksLibrary
{
public:
    enum ModeBlocks
    {
        None = 0,
        Based = 1,
        Composite = 2,
        SPARQL = 4,
        Atom = 8,
        IO = 16
    };

    BlocksLibrary();

    void loadBlocksFromFiles( const QString& folder );

    void addBlock( DiagramItemSettings* settings );
    void addBlocks( const QVector<DiagramItemSettings*>& settings_list );

    void addBlockFromJson( QString& text );
    void deleteBlocks( int modes_blocks );

    QVector<DiagramItemSettings*> getBlocks( int modes_blocks );
    int getSize();

private:
    ModeBlocks getMode( DiagramItemSettings* settings );

private:
    QMap<DiagramItemSettings*, ModeBlocks> library;
};

#endif // BLOCKSLIBRARY_H
