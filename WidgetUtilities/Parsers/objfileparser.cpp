#include <QMessageBox>
#include <QString>
#include <QFile>
#include "../../Model/wireframemesh.h"
#include "objfileparser.h"

#include <QDebug>

WireframeMesh *OBJFileParser::load(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return nullptr;

    WireframeMesh *mesh = new WireframeMesh();

    char buf[512];
    int curPos;
    int line = -1;
    try
    {
        while(!file.atEnd())
        {
           curPos = 0;
           line++;
           int read = file.readLine(buf, 512);
           for(int curPos = 0; curPos < read && isspace(buf[curPos]); curPos++);

           if(buf[curPos] == '#')
               continue;

           if(buf[curPos] == '\n' || buf[curPos] == '\0' || buf[curPos] == '\r')
               continue;

           if(buf[curPos] == 'v')
           {
               switch(buf[curPos + 1])
               {
               case 't':
                   getTextureCoordinate(mesh, buf, curPos + 2);
                   break;

               case 'n':
                   getNormal(mesh, buf, curPos + 2);
                   break;

               default:
                   if(isspace(buf[curPos + 1]))
                       getVertex(mesh, buf, curPos + 1);
                   break;
               }
           }
           else if(buf[curPos] == 'f')
               getFace(mesh, buf, curPos);
           else if(buf[curPos] == 'g')
               continue;

        }

        mesh->prepareMesh();
    }
    catch(std::invalid_argument &arg)
    {
        QMessageBox::critical(nullptr, "Error loading mesh",
            QString("Error loading mesh at line: ") + QString::number(line) +
            QString("\n Reason: ") + QString(arg.what()));

        delete mesh;
        mesh = nullptr;
    }

    file.close();

    return mesh;
}

WireframeMesh *OBJFileParser::load(const QString &&filename)
{
    return load(filename);
}

void OBJFileParser::getVertex(WireframeMesh *mesh, const char *line, int linePosition)
{
    float coords[3];
    for(int i = 0; i < 3; i++)
            coords[i] = converter.getNumber(line, linePosition);

    mesh->addVertex(QVector3D(coords[0], coords[1], coords[2]));
}

void OBJFileParser::getNormal(WireframeMesh *mesh, const char *line, int linePosition)
{
    float coords[3];
    for(int i = 0; i < 3; i++)
        coords[i] = converter.getNumber(line, linePosition);

    mesh->addNormal(QVector3D(coords[0], coords[1], coords[2]));
}

void OBJFileParser::getTextureCoordinate(WireframeMesh *mesh, const char *line, int linePosition)
{
    float coords[2];
    for(int i = 0; i < 2; i++)
        coords[i] = converter.getNumber(line, linePosition);

    mesh->addTextureCoordinate(coords[0], coords[1]);
}

void OBJFileParser::getFace(WireframeMesh *mesh, const char *line, int linePosition)
{
    mesh->addFace();
    ++linePosition;

    while(line[linePosition] != '\r' && line[linePosition] != '\n' && line[linePosition != '\0'])
        getFaceVertex(mesh, line, linePosition);

}

void OBJFileParser::getFaceVertex(WireframeMesh *mesh, const char *line, int &linePosition)
{
    while(isspace(line[linePosition]))
        linePosition++;

    char buf[32];
    int bufSize = sizeof(buf) - 1;
    for(int i = 0; i < 3; i++)
    {
        int bufPos = 0;
        while(bufPos < bufSize && line[linePosition] != '/' && !isspace(line[linePosition]))
            buf[bufPos++] = line[linePosition++];

        linePosition++;
        if(bufPos == 0)
            continue;

        buf[bufPos] = '\0';

        // Substracting 1, as indexing in .obj starts with 1, not 0
        switch(i)
        {
        case 0:
            mesh->appendVertex(converter.getNumber(buf, 0) - 1);
            break;

        case 1:
            mesh->appendTextureCoordinate(converter.getNumber(buf, 0) - 1);
            break;

        case 2:
            mesh->appendNormal(converter.getNumber(buf, 0) - 1);
        }
    }
}
