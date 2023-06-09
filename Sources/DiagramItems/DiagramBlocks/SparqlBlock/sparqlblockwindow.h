#ifndef SPARQLBLOCKWINDOW_H
#define SPARQLBLOCKWINDOW_H

#include <QCheckBox>
#include <QSpinBox>
#include <QTextEdit>

#include <diagramitematom.h>
#include <sgraphicsview.h>
#include <sparqlblocksettings.h>

class SparqlBlockWindow : public SGraphicsView
{
    Q_OBJECT
public:
    SGViewTypes typeSGView() override { return SparqlBlockWindowType; }
    int modeDiagramBlocks() override { return BlocksLibrary::ModeBlocks::Atom; }

    explicit SparqlBlockWindow( QMenu* context_menu, QWidget* parent = nullptr );

    void setSettings( SparqlBlockSettings* settings = new SparqlBlockSettings() );

    SparqlBlockSettings* getSettings();

public slots:
    // void slotOnCreateButtonClicked() override;
    void slotOnSaveButtonClicked() override;
    void slotOnOpenButtonClicked() override;
    void slotOpenQuery();
    void slotClickCheckBoxQuery();

private:
    QWidget* addCustomWidget() override;
    QWidget* addCustomBotWidget() override;

    QLineEdit* line_name_block;
    QSpinBox* spin_box_limit;
    QCheckBox* box_query;
    void createDefaultcScene();
    void clearScene();
    bool CheckCollisionArea( DiagramItemAtom* item, DiagramItemAtom* area );
    QTextEdit* query_edit;
};

#endif // SPARQLBLOCKWINDOW_H
