#include "sceneobject.h"

SceneObject::SceneObject(): QObject()
{
}

rayTraceInfo SceneObject::intersect(const QVector3D &, const QVector3D &)
{
    return rayTraceInfo();
}

const char *SceneObject::type() const
{
    return (typeid(SceneObject)).name();
}
