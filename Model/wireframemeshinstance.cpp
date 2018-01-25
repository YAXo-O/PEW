#include "wireframemeshinstance.h"
#include "../worldinfo.h"
#include "../externalmath.h"
#include "../pointtransformations.h"

#include <QDebug>

WireframeMeshInstance::WireframeMeshInstance(WireframeMesh *_mesh, QVector3D _pivotPoint): Model(),
    pivotPoint(_pivotPoint), mesh(_mesh), mat(new Material),
    transforms(4, 4), reverseTransforms(4, 4),
    bShowEdgedFaces(true), bShowVerticies(true), bShowSurface(false)
{
    transforms.loadIdentity();
    reverseTransforms.loadIdentity();
}

rayTraceInfo WireframeMeshInstance::intersect(const QVector3D &_origin, const QVector3D &_dir)
{
    if(!bVisible)
        return rayTraceInfo();

    // Here we should apply transformations to an intersection point (reverse transformation)
    QVector3D origin(_origin);
    QVector3D dir(_dir);
    rayToMeshSpace(origin, dir);
    if(mesh)
    {
        traceIntersectInfo meshIntersection = mesh->trace(origin, dir);
        pointFromMeshSpace(meshIntersection.intersection);
        rayTraceInfo result;
        if(meshIntersection.bIntersects)
            result.color = mat->getColor(meshIntersection, dir);

        result.bIntersects = meshIntersection.bIntersects;
        result.param = meshIntersection.param;

        return result;
    }
    else
        return Model::intersect(origin, dir);
}

bool WireframeMeshInstance::blocks(const QVector3D &_origin, const QVector3D &_dir)
{
    // Also transform ray
    QVector3D origin(_origin);
    QVector3D dir(_dir);
    rayToMeshSpace(origin, dir);
    if(mesh)
        return mesh->blocks(origin, dir);
    else
        return Model::blocks(origin, dir);
}

bool WireframeMeshInstance::blocks(const QVector3D &_origin, const QVector3D &_dir, const QVector3D &_exclude)
{
    QVector3D origin(_origin);
    QVector3D dir(_dir);
    QVector3D exclude(_exclude);
    rayToMeshSpace(origin, dir);
    pointToMeshSpace(exclude);
    if(mesh)
        return mesh->blocks(origin, dir, exclude);
    else
        return Model::blocks(origin, dir, exclude);
}

bool WireframeMeshInstance::blocks(const QVector3D &origin, const QVector3D &dir, float maxDist)
{
    if(mesh)
        return mesh->blocks(origin, dir, maxDist);

    return false;
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

Material &WireframeMeshInstance::material()
{
    return *mat;
}

void WireframeMeshInstance::move(QVector3D shift)
{
    transforms *= transformations::moveMatrix(-shift);
    reverseTransforms = transformations::moveMatrix(shift);
}

void WireframeMeshInstance::moveTo(QVector3D point)
{
    move(point - pivotPoint);
}

void WireframeMeshInstance::rotate(QVector3D rotator)
{
    Matrix shift = transformations::moveMatrix(-pivotPoint);
    Matrix shiftBack = transformations::moveMatrix(pivotPoint);
    transforms *= shift*transformations::rotationMatrix(-rotator)*shiftBack;
    reverseTransforms = shift*transformations::rotationMatrix(rotator)*shiftBack;
}

SceneObject *WireframeMeshInstance::copy()
{
    WireframeMeshInstance *c = new WireframeMeshInstance(mesh, pivotPoint);
    c->setVisible(true);
    c->changeMaterial(mat);
    WorldInfo::getInstance().registerObject(c);

    return c;

}

void WireframeMeshInstance::changeMaterial(Material *_mat)
{
    mat = _mat;
}

void WireframeMeshInstance::rayToMeshSpace(QVector3D &origin, QVector3D &dir)
{
    pointToMeshSpace(origin);
    dir = (Matrix(dir)*transforms).toVector();
}

void WireframeMeshInstance::pointToMeshSpace(QVector3D &point)
{
    point = (Matrix(point)*transforms).toVector();
}

void WireframeMeshInstance::rayFromMeshSpace(QVector3D &origin, QVector3D &dir)
{
    pointFromMeshSpace(origin);
    dir = (Matrix(dir)*reverseTransforms).toVector();
}

void WireframeMeshInstance::pointFromMeshSpace(QVector3D &point)
{
    point = (Matrix(point)*reverseTransforms).toVector();
}


