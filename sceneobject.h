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
    virtual bool blocks(const QVector3D &origin, const QVector3D &dir);
    virtual bool blocks(const QVector3D &origin, const QVector3D &dir, const QVector3D &exclude);
    virtual bool blocks(const QVector3D &origin, const QVector3D &dir, float maxDist);
    virtual const char *type() const;

    virtual void move(QVector3D shift);
    virtual void rotate(QVector3D rotator);
    virtual void scale(QVector3D scaleFactor);
};

#endif // SCENEOBJECT_H
