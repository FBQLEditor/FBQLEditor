#include "basicblocksettings.h"

#include <QJsonObject>

BasicBlockSettings::BasicBlockSettings()
{
    block_name = "BasicBlock";
    label = true;
    label_text = "label";
    line_edit = true;
    line_edit_text = "";
    script = "";
    type_image = "self";
    pixmap = image();
}

bool BasicBlockSettings::CheckSettings( const QJsonObject& object )
{
    if ( object["Header"]["Type"].toString() == "Basic" )
    {
        return true;
    }
    return false;
}

void BasicBlockSettings::setSettingFromJson( const QJsonObject& object )
{
    if ( CheckSettings( object ) )
    {

        QJsonObject header = object["Header"].toObject();
        QJsonObject body = object["Body"].toObject();

        block_name = header["Name"].toString();

        pixmap = pixmapFrom( body["Image"] );
        flag_custom_image = body["Flag_Custom_Image"].toBool();
        label = body["Flag_Label"].toBool();
        line_edit = body["Flag_Edit"].toBool();
        label_text = body["Text_Label"].toString();
        line_edit_text = body["Text_Edit"].toString();
        pos = pointFromJsonObject( body["Pos"] );
        script = body["Script"].toString();
    }
}

QJsonObject BasicBlockSettings::getJsonFromSetting()
{
    QJsonObject object;

    QJsonObject header;
    QJsonObject body;

    header.insert( "Name", block_name );
    header.insert( "Type", "Basic" );

    body.insert( "Image", jsonValFromPixmap( pixmap ) );
    body.insert( "Flag_Custom_Image", flag_custom_image );
    body.insert( "Flag_Label", label );
    body.insert( "Flag_Edit", line_edit );
    body.insert( "Text_Label", label_text );
    body.insert( "Text_Edit", line_edit_text );
    body.insert( "Pos", jsonFromPointF( pos ) );
    body.insert( "Script", script );

    object.insert( "Header", header );
    object.insert( "Body", body );

    return object;
}

QPixmap BasicBlockSettings::image() const
{
    return {};
}
