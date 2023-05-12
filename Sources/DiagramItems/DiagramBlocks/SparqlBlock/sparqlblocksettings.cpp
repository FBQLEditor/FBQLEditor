#include "sparqlblocksettings.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QUrl>

SparqlBlockSettings::SparqlBlockSettings()
{
    block_name = "SparqlBlock";
    pixmap = image();
    limit = 20;
}

SparqlBlockSettings::~SparqlBlockSettings()
{
    clear();
}

void SparqlBlockSettings::setSettingFromJson( const QJsonObject& object )
{
    if ( object["Header"]["Type"].toString() == "Sparql" )
    {
        areas.clear();
        lines.clear();

        QJsonValue header = object["Header"];
        QJsonValue body = object["Body"];

        block_name = header["Name"].toString();
        // type_image = value["type_img"].toString();
        // pixmap = pixmapFrom( body["Image"] );
        limit = body["Limit"].toInt();
        start_area = body["Start_Area"].toInt();
        pos = pointFromJsonObject( body["Pos"] );
        query = body["Query"].toString();

        QJsonArray areas_array = body["Areas"].toArray();
        for ( const QJsonValue& area : areas_array )
        {
            auto blocks_array = area["Blocks"].toArray();
            auto lines_array = area["Lines"].toArray();
            auto settings = area["Settings"];

            AreaSaver area_saver;
            for ( const QJsonValue& block : blocks_array )
            {
                AtomBlockSettings* setting = new AtomBlockSettings();
                setting->setSettingFromJson( block.toObject() );
                area_saver.blocks.push_back( setting );
            }

            for ( const QJsonValue& line : lines_array )
            {
                area_saver.lines.push_back( { line["Start"].toInt(), line["End"].toInt(), line["Text"].toString() } );
            }

            area_saver.settings = new AtomBlockSettings();
            area_saver.settings->setSettingFromJson( settings.toObject() );
            area_saver.filter = area["Filter"].toString();

            areas.push_back( area_saver );
        }

        QJsonArray lines_array = body["Lines"].toArray();
        for ( const QJsonValue& line : lines_array )
        {
            lines.push_back( { line["Start"].toInt(), line["End"].toInt(), line["Text"].toString() } );
        }
    }
}

QJsonArray SparqlBlockSettings::getJsonArrayFromLineSaver( const QVector<LineSaver>& lines )
{
    QJsonArray lines_array;
    for ( const auto& line : lines )
    {
        QJsonObject line_obj;
        line_obj.insert( "Text", line.text );
        line_obj.insert( "Start", line.start_block );
        line_obj.insert( "End", line.end_block );
        lines_array.push_back( line_obj );
    }
    return lines_array;
}

QJsonObject SparqlBlockSettings::getJsonFromSetting()
{
    QJsonObject json_object;

    QJsonObject header;
    QJsonObject body;

    header.insert( "Type", "Sparql" );
    header.insert( "Name", block_name );

    body.insert( "Limit", limit );
    body.insert( "Start_Area", start_area );
    body.insert( "Pos", jsonFromPointF( pos ) );
    body.insert( "Query", query );

    body.insert( "Lines", getJsonArrayFromLineSaver( lines ) );

    QJsonArray areas_array;
    for ( const auto& area : areas )
    {
        QJsonObject area_obj;
        area_obj.insert( "Filter", area.filter );
        area_obj.insert( "Settings", area.settings->getJsonFromSetting() );
        area_obj.insert( "Lines", getJsonArrayFromLineSaver( area.lines ) );
        QJsonArray blocks_array;
        for ( const auto& block : area.blocks )
        {
            blocks_array.push_back( block->getJsonFromSetting() );
        }
        area_obj.insert( "Blocks", blocks_array );
        areas_array.push_back( area_obj );
    }
    body.insert( "Areas", areas_array );

    json_object.insert( "Header", header );
    json_object.insert( "Body", body );

    return json_object;
}

QString SparqlBlockSettings::getQuery()
{
    QString request;
    MainSettingsMaster master;
    auto prefixes = master.getSettings<QStringList>( "SPARQL_prefixes" );
    for ( auto& prefix : prefixes )
    {
        request += prefix + "\n";
    }
    request += "\nSELECT *";

    QString body = "";
    QMap<int, QString> stack = { { start_area, "" } };
    while ( !stack.empty() )
    {
        int index = stack.keys().at( 0 );
        QString name = stack[index];
        AreaSaver area = areas.at( index );
        stack.remove( index );

        QString area_str = name + "\n{\n";
        for ( const auto& line : area.lines )
        {
            QString str = ( ( DEFAULT_VAR == area.blocks.at( line.start_block )->type_block ) ? "?" : "" )
                + area.blocks.at( line.start_block )->text;
            str += " " + line.text;
            str += " "
                + QString( ( DEFAULT_VAR == area.blocks.at( line.end_block )->type_block ) ? "?" : "" )
                + area.blocks.at( line.end_block )->text;
            str += ".\n";
            area_str += str;
        }
        if ( !area.filter.isEmpty() )
        {
            area_str += "FILTER ( " + area.filter + ")\n";
        }
        area_str += "}\n";
        body += area_str;

        for ( const auto& line : lines )
        {
            if ( line.start_block == index )
            {
                stack.insert( line.end_block, line.text );
            }
        }
    }

    request += "\nWHERE\n"
               "{\n";
    request += "  " + body;
    request += "} LIMIT " + QString::number( limit );
    return request;
}

QString SparqlBlockSettings::getScript()
{
    MainSettingsMaster master;
    auto dataset_name = master.getSettings<QString>( "SPARQL_dataset_name" );
    auto fuseki_ip = master.getSettings<QString>( "SPARQL_fuseki_ip" );
    auto fuseki_port = master.getSettings<QString>( "SPARQL_fuseki_port" );

    if ( dataset_name.isEmpty() )
    {
        qDebug() << "Dataset is Empty";
    }

    QString script = "var xmlHttp = new XMLHttpRequest(network);\n"
                     "xmlHttp.setUrl(\"http://"
        + fuseki_ip + ":"
        + fuseki_port + "/"
        + dataset_name + "/query\");\n"
                         "xmlHttp.open(\"POST\", \"/\");\n"
                         "xmlHttp.setRequestHeader(\"Connection\", \"keep-alive\");\n"
                         "xmlHttp.setRequestHeader(\"Accept\", \"application/sparql-results+json\");\n"
                         "var answer = xmlHttp.send(";

    script += "\"query=" + QUrl::toPercentEncoding( query.isEmpty() ? getQuery() : query ) + "\");\n";
    script += "json_obj = JSON.parse( answer );\n"
              "array = json_obj.results.bindings;\n"
              "y.push( array.length );";

    return script;
}

QPixmap SparqlBlockSettings::image() const
{
    return QPixmap( ":/Sources/images/sparqlicon.jpg" );
}

SparqlBlockSettings* SparqlBlockSettings::CreateTemplateSparqlSettings()
{
    auto settings = new SparqlBlockSettings();
    AreaSaver area_saver;
    area_saver.settings = AtomBlockSettings::GetAreaAtomBlock();
    area_saver.settings->pos = QPointF( 2500, 2500 );
    settings->areas.push_back( area_saver );
    return settings;
}

void SparqlBlockSettings::clear()
{
    for ( auto& area : areas )
    {
        /*if ( area.settings != nullptr )
            delete area.settings;
        for ( auto& block : area.blocks )
        {
            if ( block != nullptr )
                delete block;
        }*/
        area.blocks.clear();
    }
    areas.clear();
}
