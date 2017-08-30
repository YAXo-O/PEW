#include "model.h"

Model::Model(): SceneObject()
{
}

rayTraceInfo Model::intersect(const QVector3D &origin, const QVector3D &dir )
{
    return SceneObject::intersect(origin, dir);
}

const char *Model::type() const
{
    return typeid(Model).name();
}
