#ifndef LIGHTINFO_H
#define LIGHTINFO_H

#include <QVector3D>
#include <QColor>

struct lightInfo
{
    QVector3D position;
    QColor color;
    float intensity;
};

#endif // LIGHTINFO_H
