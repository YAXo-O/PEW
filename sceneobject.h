#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QObject>
#include <typeinfo>
#include "tracinginfo.h"

class SceneObject: public QObject
{
    Q_OBJECT
public:
    SceneObject();
    virtual ~SceneObject() {}

    virtual rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir);
    virtual const char *type() const;

};

#endif // SCENEOBJECT_H
