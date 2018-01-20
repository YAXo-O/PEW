#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#include "../Utilities/stringconverter.h"

class WireframeMesh;
class QString;

class OBJFileParser
{
public:
    OBJFileParser() = default;
    ~OBJFileParser() = default;

    WireframeMesh *load(const QString &filename);
    WireframeMesh *load(const QString &&filename);

private:
    StringConverter converter;

    void getVertex(WireframeMesh *mesh, const char *line, int linePosition);
    void getNormal(WireframeMesh *mesh, const char *line, int linePosition);
    void getTextureCoordinate(WireframeMesh *mesh, const char *line, int linePosition);
    void getFace(WireframeMesh *mesh, const char *line, int linePosition);
    void getFaceVertex(WireframeMesh *mesh, const char *line, int &linePosition);

};

#endif // OBJFILEPARSER_H
