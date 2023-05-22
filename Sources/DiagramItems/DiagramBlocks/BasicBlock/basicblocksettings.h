#ifndef BASICBLOCKSETTINGS_H
#define BASICBLOCKSETTINGS_H

#include <QPixmap>
#include <QString>
#include <diagramitemsettings.h>

class BasicBlockSettings : public DiagramItemSettings
{
public:
    int typeSettings() const override { return BasicItemSettingsType; };

    BasicBlockSettings();

    void setSettingFromJson( const QJsonObject& object ) override;
    QJsonObject getJsonFromSetting() override;
    QPixmap image() const override;
    QString getScript() override { return script; }

    static bool CheckSettings( const QJsonObject& object );

public:
    bool label;
    QString label_text;

    bool line_edit;
    QString line_edit_text;

    QString script;

    QString type_image;
    bool flag_custom_image;
};

#endif // BASICBLOCKSETTINGS_H
