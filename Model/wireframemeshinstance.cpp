#include "wireframemeshinstance.h"

WireframeMeshInstance::WireframeMeshInstance(WireframeMesh *_mesh, QVector3D _pivotPoint): Model(),
    pivotPoint(_pivotPoint), mesh(_mesh),
    bShowEdgedFaces(true), bShowVerticies(true), bShowSurface(false)
{
}

rayTraceInfo WireframeMeshInstance::intersect(const QVector3D &origin, const QVector3D &dir)
{
    // Here we should apply transformations to an intersection point (reverse transformation)
    if(mesh)
        return mesh->intersect(origin, dir, bShowEdgedFaces, bShowVerticies, bShowSurface);
    else
        return Model::intersect(origin, dir);
}

WireframeMesh *WireframeMeshInstance::getMesh() const
{
    return mesh;
}

void WireframeMeshInstance::setMesh(WireframeMesh *value)
{
    mesh = value;
}

QVector3D WireframeMeshInstance::getPivotPoint() const
{
    return pivotPoint;
}

void WireframeMeshInstance::setPivotPoint(const QVector3D &value)
{
    pivotPoint = value;
}

const char *WireframeMeshInstance::type() const
{
    return typeid(WireframeMeshInstance).name();
}
