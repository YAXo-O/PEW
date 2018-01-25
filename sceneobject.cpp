#include "sceneobject.h"

SceneObject::SceneObject(): QObject(), bVisible(true)
{
}

rayTraceInfo SceneObject::intersect(const QVector3D &, const QVector3D &)
{
    return rayTraceInfo();
}

bool SceneObject::blocks(const QVector3D &, const QVector3D &)
{
    return false;
}

bool SceneObject::blocks(const QVector3D &, const QVector3D &, const QVector3D &)
{
    return false;
}

bool SceneObject::blocks(const QVector3D &, const QVector3D &, float )
{
    return false;
}

const char *SceneObject::type() const
{
    return (typeid(SceneObject)).name();
}

void SceneObject::move(QVector3D )
{
}

void SceneObject::moveTo(QVector3D)
{
}

void SceneObject::rotate(QVector3D )
{
}

void SceneObject::scale(QVector3D)
{
}

SceneObject *SceneObject::copy()
{
    return new SceneObject();
}

void SceneObject::setVisible(bool _bVisible)
{
    bVisible = _bVisible;
}
