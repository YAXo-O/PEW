#ifndef TRACINGINFO_H
#define TRACINGINFO_H

#include <QVector3D>
#include <QVector2D>
#include <QColor>

struct rayTraceInfo
{
    QColor color;
    double param = -100; // It's faster to compare parameter rather than points' lengths
    bool bIntersects = false;
};

struct traceIntersectInfo
{
    QVector3D intersection;
    QVector3D normal;
    QVector2D uvs;
    double param = -100;
    bool bIntersects = false;
};

#endif // TRACINGINFO_H
