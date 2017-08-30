#ifndef TRACINGINFO_H
#define TRACINGINFO_H

#include <QVector3D>
#include <QColor>

struct rayTraceInfo
{
    QVector3D intersection;
    QColor color;
    double param = -100; // It's faster to compare parameter rather than points' lengths
    bool bIntersects = false;
};

#endif // TRACINGINFO_H
