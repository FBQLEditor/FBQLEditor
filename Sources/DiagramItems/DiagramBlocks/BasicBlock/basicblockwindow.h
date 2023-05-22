#ifndef BASICBLOCKWINDOW_H
#define BASICBLOCKWINDOW_H

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include <diagramitembasic.h>
#include <swidget.h>

class BasicBlockWindow : public SWidget
{
    Q_OBJECT
public:
    enum BasicMode
    {
        CreateMode = 0,
        ReworkMode = 1
    };
    SWidgetTypes typeSWidget() override { return BasicBlockWindowType; }
    int modeDiagramBlocks() override { return BlocksLibrary::ModeBlocks::None; }

    explicit BasicBlockWindow( const BasicMode& mode, QWidget* parent = nullptr );

    void createWidget();
    void setMode( const BasicMode& mode );
    void setBlockOnRework( DiagramItemBasic* item );
    void setSettings( BasicBlockSettings* settings );

    QString getName( const QString& path );

private slots:
    void slotOnSaveButtonClicked() override;
    void slotOnOpenButtonClicked() override;

    void slotInfo();
    void slotTestScript();
    void slotSetImage();
    void slotDeleteImage();
    void slotSetName( const QString& name );

    BasicBlockSettings* getSettings();

signals:
    void changeNameWindow( QString );
    void error( QString );

private:
    BasicMode mode_;
    DiagramItemBasic* item_on_rework;

    QPixmap pixmap;
    QLabel* label_pixmap;
    QLineEdit* line_name;
    QLineEdit* line_line_edit;
    QLineEdit* line_label;
    QCheckBox* check_line_edit;
    QCheckBox* check_label;
    QTextEdit* text_edit;
};

#endif // BASICBLOCKWINDOW_H
