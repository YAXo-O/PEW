#include <QMap>
#include "meshmanager.h"
#include "WidgetUtilities/Parsers/objfileparser.h"
#include "Model/wireframemesh.h"

WireframeMesh *MeshManager::getMesh(const QString &filename)
{
    if(table.contains(filename))
        return table[filename];

    OBJFileParser parser;
    WireframeMesh *mesh = parser.load(filename);
    table[filename] = mesh;

    return mesh;
}

WireframeMesh *MeshManager::getMesh(const QString &&filename)
{
    return getMesh(filename);
}

