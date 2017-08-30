#include "wireframemesh.h"

WireframeMesh::WireframeMesh(): Model()
{
}

rayTraceInfo WireframeMesh::intersect(const QVector3D &origin, const QVector3D &dir)
{
    // Do its magic here

    return Model::intersect(origin, dir);
}

rayTraceInfo WireframeMesh::intersect(const QVector3D &origin, const QVector3D &dir,
                                      bool bEdgedFaces, bool bVerticies, bool bSurface)
{
    // Real magic is here
    double radius = 0;
    QVector3D center = {0, 0, 0};
    getSphere(center, radius);

    if(!sphereTest(origin, dir, center, radius))
        return intersect(origin, dir);

    // Will have to search throw all the faces, in order to find exact intersect points

    return intersect(origin, dir);
}

void WireframeMesh::addVertex(const QVector3D &vertex)
{
    verticies.append(vertex);
}

void WireframeMesh::addVertex(const QVector3D &&vertex)
{
    verticies.append(vertex);
}

void WireframeMesh::addUniqueVertex(const QVector3D &vertex)
{
    for(auto i:verticies)
        if(i == vertex)
            return;

    verticies.append(vertex);
}

void WireframeMesh::addUniqueVertex(const QVector3D &&vertex)
{
    addUniqueVertex(vertex);
}

void WireframeMesh::addFace()
{
    faces.append(face());
}

void WireframeMesh::addFaceVertex(const QVector3D &vertex)
{
    addUniqueVertex(vertex);
    faces.last().verts.push_back(verticies.indexOf(vertex));
}

void WireframeMesh::addFaceVertex(const QVector3D &&vertex)
{
    addFaceVertex(vertex);
}

void WireframeMesh::addFaceVertex(size_t id)
{
    faces.last().verts.push_back(id);
}

void WireframeMesh::addFaceColor(const QColor &col)
{
    faces.last().color = col;
}

void WireframeMesh::addFaceColor(const QColor &&col)
{
    addFaceColor(col);
}

void WireframeMesh::faceNormal()
{
    QVector3D a = verticies[faces.last().verts[0]];
    QVector3D b = verticies[faces.last().verts[1]];
    QVector3D c = verticies[faces.last().verts[2]];
    faces.last().normal = QVector3D::crossProduct(b - a, c - a);
}

void WireframeMesh::reverseNormal()
{
    faces.last().normal *= -1;
}

void WireframeMesh::setVisible(bool visible)
{
    faces.last().bVisible = visible;
}

const char *WireframeMesh::type() const
{
    return typeid(WireframeMesh).name();
}

void WireframeMesh::getSphere(QVector3D &center, double &radius)
{
    center = {0, 0, 0};
    size_t count = 0;

    for(auto i:verticies)
    {
        count++;
        center += i;
    }
    center /= count;

    radius = 0;
    for(auto i:verticies)
    {
        double curLen = (i - center).length();
        if(curLen > radius)
            radius = curLen;
    }
}

bool WireframeMesh::sphereTest(const QVector3D &origin, const QVector3D &dir, const QVector3D &center, double radius)
{
    if(center.distanceToLine(origin, dir) > radius)
        return false;

    return true;
}
