#include <QVector2D>
#include "wireframemesh.h"
#include "../externalmath.h"

#include <QDebug>
#include <ctime>

WireframeMesh::WireframeMesh(): Model(), sphereCenter(0, 0, 0), radius(0)
{
}

WireframeMesh::~WireframeMesh()
{
}

traceIntersectInfo WireframeMesh::trace(const QVector3D &origin, const QVector3D &dir)
{
    // Real magic is here
    if(!sphereTest(origin, dir))
        return traceIntersectInfo();

    return findIntersection(origin, dir);
}

bool WireframeMesh::blocks(const QVector3D &origin, const QVector3D &dir)
{
    if(!sphereTest(origin, dir))
        return false;

    const double eps = 1e-4;

    for(auto i : faces)
    {
        if(!isFacing(dir, i))
            continue;

        QVector3D A = verticies[i.verts[0]];
        QVector3D B = verticies[i.verts[1]];
        QVector3D C = verticies[i.verts[2]];

        QVector3D V = A - origin;

        QVector3D normal =  QVector3D::crossProduct(A - B, A - C).normalized();

        double distanceAlongNormal = QVector3D::dotProduct(normal, V);
        double reachability = QVector3D::dotProduct(normal, dir);

        if(reachability != 0)
        {
            double t = distanceAlongNormal/reachability;
            QVector3D intersection = origin + dir*t;
            if(t >= -eps && onFace(intersection, i))
                return true;
        }
    }

    return false;
}

bool WireframeMesh::blocks(const QVector3D &origin, const QVector3D &dir, const QVector3D &exclude)
{
    if(!sphereTest(origin, dir))
        return false;

    const double eps = 1e-3;

    for(auto i : faces)
    {
        if(!isFacing(dir, i))
            continue;

        QVector3D A = verticies[i.verts[0]];
        QVector3D B = verticies[i.verts[1]];
        QVector3D C = verticies[i.verts[2]];

        QVector3D V = A - origin;

        QVector3D normal =  QVector3D::crossProduct(A - B, A - C).normalized();

        double distanceAlongNormal = QVector3D::dotProduct(normal, V);
        double reachability = QVector3D::dotProduct(normal, dir);

        if(reachability != 0)
        {
            double t = distanceAlongNormal/reachability;
            QVector3D intersection = origin + dir*t;
            if(!externalMath::fuzzyCompare(intersection, exclude, eps) && t >= -eps && onFace(intersection, i))
                return true;
        }
    }

    return false;
}

bool WireframeMesh::blocks(const QVector3D &origin, const QVector3D &dir, float maxDist)
{
    if(!sphereTest(origin, dir))
        return false;

    const double eps = 1e-4;

    for(auto i : faces)
    {
        if(!isFacing(dir, i))
            continue;

        QVector3D A = verticies[i.verts[0]];
        QVector3D B = verticies[i.verts[1]];
        QVector3D C = verticies[i.verts[2]];

        QVector3D V = (A - origin);

        QVector3D normal =  QVector3D::crossProduct(A - B, A - C);

        double distanceAlongNormal = QVector3D::dotProduct(normal, V);
        double reachability = QVector3D::dotProduct(normal, dir);

        if(reachability != 0)
        {
            double t = distanceAlongNormal/reachability;
            QVector3D intersection = origin + dir*t;
            if(t >= -eps && t <= maxDist && onFace(intersection, i))
                return true;
        }
    }

    return false;
}

void WireframeMesh::addVertex(const QVector3D &vertex)
{
    verticies.append(vertex);
}

void WireframeMesh::addVertex(const QVector3D &&vertex)
{
    verticies.append(vertex);
}

void WireframeMesh::addNormal(const QVector3D &normal)
{
    normals.append(normal);
}

void WireframeMesh::addNormal(const QVector3D &&normal)
{
    addNormal(normal);
}

void WireframeMesh::addTextureCoordinate(float u, float v)
{
    uvs.append(QVector2D(u, v));
}

void WireframeMesh::addFace()
{
    faces.append(face());
}

void WireframeMesh::appendVertex(size_t id)
{
    faces.last().verts.append(id);
}

void WireframeMesh::appendNormal(size_t id)
{
    faces.last().normals.append(id);
}

void WireframeMesh::appendTextureCoordinate(size_t id)
{
    faces.last().uvs.append(id);
}

void WireframeMesh::prepareMesh()
{
    getSphere();
}

const char *WireframeMesh::type() const
{
    return typeid(WireframeMesh).name();
}

void WireframeMesh::getSphere()
{
    // Find center
    sphereCenter = {0, 0, 0};
    size_t count = 0;
    for(auto i:verticies)
    {
        count++;
        sphereCenter += i;
    }
    sphereCenter /= count;

    // Find radius
    radius = 0;
    for(auto i:verticies)
    {
        double curLen = (i - sphereCenter).length();
        if(curLen > radius)
            radius = curLen;
    }
}

traceIntersectInfo WireframeMesh::findIntersection(const QVector3D &origin, const QVector3D &dir)
{
    traceIntersectInfo result;

    for(auto i : faces)
    {
        if(!isFacing(dir, i))
            continue;

        QVector3D A = verticies[i.verts[0]];
        QVector3D B = verticies[i.verts[1]];
        QVector3D C = verticies[i.verts[2]];

        QVector3D V = A - origin;

        QVector3D normal =  QVector3D::crossProduct(A - B, A - C).normalized();

        double distanceAlongNormal = QVector3D::dotProduct(normal, V);
        double reachability = QVector3D::dotProduct(normal, dir);

        if(reachability != 0)
        {
            double t = distanceAlongNormal/reachability;
            QVector3D intersection = origin + dir*t;

            if((!result.bIntersects || t < result.param) && onFace(intersection, i))
            {
                result.bIntersects = true;
                result.param = t;
                result.intersection = intersection;

                // Find scanline
                scanAxes axes;

                QVector3D &firstPoint = verticies[i.verts[0]];
                QVector3D &secondPoint = verticies[i.verts[1]];
                QVector3D &thirdPoint = verticies[i.verts[2]];
                QVector3D normal = QVector3D::crossProduct(secondPoint - firstPoint, thirdPoint - firstPoint);
                if(normal.y())
                    axes = SA_Z;
                else if(normal.z())
                    axes = SA_X;
                else
                    axes = SA_Y;

                result.uvs = findUv(result.intersection, i, axes);
                result.normal = findNormal(result.intersection, i, axes).normalized();
            }
        }
    }

    return result;
}

bool WireframeMesh::isFacing(const QVector3D &dir, const face &curFace)
{
    const double eps = 1e-4;
    // Getting average normal from vertices
    QVector3D average{0, 0, 0};

    for(auto i : curFace.normals)
        average += normals[i];

    return  QVector3D::dotProduct(average, dir) <= eps;
}


bool WireframeMesh::onFace(const QVector3D &point, const face &face)
{
    return crossProductCheck(point, face);
}

bool WireframeMesh::crossProductCheck(const QVector3D &point, const face &checkFace)
{
    const double eps = 1e-4;

    QVector3D &firstPoint = verticies[checkFace.verts[0]];
    QVector3D &secondPoint = verticies[checkFace.verts[1]];
    QVector3D reference = QVector3D::crossProduct(secondPoint - firstPoint, point - firstPoint);

    // Lies on a line of a segment?
    if(externalMath::fuzzyCompare(reference, externalMath::nullVector, eps))
    {
        double t = -1;
        QVector3D u = secondPoint - firstPoint;
        QVector3D pointVector = point - firstPoint;

        if(fabs(u.x()) > eps)
            t = pointVector.x()/u.x();
        else if(fabs(u.y()) > eps)
            t = pointVector.y()/u.y();
        else if(fabs(u.z()) > eps)
            t = pointVector.z()/u.z();
        else
            return false; // Vertices are the same - incorrect model

        if(fabs(t) < eps)
            t = 0;
        if(fabs(t - 1) < eps)
            t = 1;

        return t >= 0 && t <= 1;
    }

    int faceVerts = checkFace.verts.count();
    for(int i = 1; i < faceVerts; i++)
    {
        int id = i + 1;
        if(id == faceVerts)
            id = 0;

        QVector3D A = verticies[checkFace.verts[i]];
        if(externalMath::fuzzyCompare(A, point, eps))
            return true; // Lies on a vertex
        QVector3D pointVector = point - A;
        QVector3D sideVector = verticies[checkFace.verts[id]] - A;

        QVector3D currentVector = QVector3D::crossProduct(sideVector, pointVector);
        if(externalMath::fuzzyCompare(currentVector, externalMath::nullVector, eps))
            continue;

        double dotProduct = QVector3D::dotProduct(reference, currentVector);
        if(fabs(dotProduct) < eps)
            dotProduct = 0;
        if(dotProduct < 0)
            return false;
    }

    return true;
}

bool WireframeMesh::rayCheck(const QVector3D &point, const face &checkFace)
{
    double count = 0;

    QVector3D &A = verticies[checkFace.verts[0]];
    QVector3D &B = verticies[checkFace.verts[1]];

    QVector3D ray = (A + B)/2 - point;
    const int vertCount = checkFace.verts.count();
    for(int i = 0; i < vertCount; i++)
    {
        int iNext = i+1;
        if(iNext == vertCount)
            iNext = 0;

        double result =externalMath::doRaySegmentIntersect(point, ray, verticies[checkFace.verts[i]], verticies[checkFace.verts[iNext]]);
        if(result == 2)
            return true;
        count += result;
    }

    return int(count)%2;
}

QVector2D WireframeMesh::findUv(const QVector3D &point, const face &checkFace, scanAxes axes)
{
    const double eps = 1e-3;

    int i = 0;
    uvLoopHolder holderA = uvLoop(point, checkFace, axes, i);
    if(holderA.bVertex)
        return holderA.uv;
    uvLoopHolder holderB = uvLoop(point, checkFace, axes, i);
    if(holderB.bVertex)
        return holderB.uv;

    QVector3D dir = holderB.point - holderA.point;
    double t = 0;
    if(fabs(dir.x()) > eps)
        t = (point.x() - holderA.point.x())/dir.x();
    else if(fabs(dir.y()) > eps)
        t = (point.y() - holderA.point.y())/dir.y();
    else
        t = (point.z() - holderA.point.z())/dir.z();

    if(t > 1.f)
        t = 1.f;
    else if (t < 0)
        t = 0;

    return (holderA.uv + t*(holderB.uv - holderA.uv));
}

QVector3D WireframeMesh::findNormal(const QVector3D &point, const face &checkFace, scanAxes axes)
{
    const double eps = 1e-3;

    int i = 0;
    normalLoopHolder holderA = normalLoop(point, checkFace, axes, i);
    if(holderA.bVertex)
        return holderA.normal;
    normalLoopHolder holderB = normalLoop(point, checkFace, axes, i);
    if(holderB.bVertex)
        return holderB.normal;

    QVector3D dir = holderB.point - holderA.point;
    double t = 0;
    if(fabs(dir.x()) > eps)
        t = (point.x() - holderA.point.x())/dir.x();
    else if(fabs(dir.y()) > eps)
        t = (point.y() - holderA.point.y())/dir.y();
    else
        t = (point.z() - holderA.point.z())/dir.z();

    if(t > 1.f)
        t = 1.f;
    else if (t < 0)
        t = 0;

    return holderA.normal + t*(holderB.normal - holderA.normal);
}

uvLoopHolder WireframeMesh::uvLoop(const QVector3D &point, const face &checkFace, scanAxes scan, int &i)
{
    const double eps = 1e-4;
    const int vCount = checkFace.verts.count();

    uvLoopHolder holder;
    // Finding point
    bool bGo = true;
    for(; (i < vCount) && bGo; i++)
    {
        int iNext = i+1;
        if(iNext == vCount)
            iNext = 0;

        QVector3D s = verticies[checkFace.verts[i]];
        QVector3D e = verticies[checkFace.verts[iNext]];

        if(externalMath::fuzzyCompare(s, point, eps))
        {
            holder.uv = uvs[i];
            holder.bVertex = true;

            return holder;
        }
        if(externalMath::fuzzyCompare(e, point, eps))
        {
            holder.uv = uvs[iNext];
            holder.bVertex = true;

            return holder;
        }

        // Axes specific action
        if( (externalMath::getComponent(s, scan) >= externalMath::getComponent(point, scan)
             && externalMath::getComponent(e, scan) <= externalMath::getComponent(point, scan))
             || (externalMath::getComponent(s, scan) <= externalMath::getComponent(point, scan)
             && externalMath::getComponent(e, scan) >= externalMath::getComponent(point, scan)) )
        {
            // We've just found an edge of point;
            QVector3D dir = e - s;
            if(externalMath::getComponent(dir, scan) == 0)
                continue;
            double t = (externalMath::getComponent(point, scan) -
                        externalMath::getComponent(s, scan))/(externalMath::getComponent(dir, scan));
            holder.point = s + t*dir;

            QVector2D sUV = uvs[checkFace.uvs[i]];
            QVector2D eUV = uvs[checkFace.uvs[iNext]];
            holder.uv = sUV + t*(eUV - sUV);

            bGo = false;
        }

    }

    return holder;
}

normalLoopHolder WireframeMesh::normalLoop(const QVector3D &point, const face &checkFace, scanAxes scan, int &i)
{
    const double eps = 1e-4;
    const int vCount = checkFace.verts.count();

    normalLoopHolder holder;
    // Finding point
    bool bGo = true;
    for(; (i < vCount) && bGo; i++)
    {
        int iNext = i+1;
        if(iNext == vCount)
            iNext = 0;

        QVector3D s = verticies[checkFace.verts[i]];
        QVector3D e = verticies[checkFace.verts[iNext]];

        if(externalMath::fuzzyCompare(s, point, eps))
        {
            holder.normal = normals[i];
            holder.bVertex = true;

            return holder;
        }
        if(externalMath::fuzzyCompare(e, point, eps))
        {
            holder.normal = normals[iNext];
            holder.bVertex = true;

            return holder;
        }

        // Axes specific action
        if( (externalMath::getComponent(s, scan) >= externalMath::getComponent(point, scan)
             && externalMath::getComponent(e, scan) <= externalMath::getComponent(point, scan))
             || (externalMath::getComponent(s, scan) <= externalMath::getComponent(point, scan)
             && externalMath::getComponent(e, scan) >= externalMath::getComponent(point, scan)) )
        {
            // We've just found an edge of point;
            QVector3D dir = e - s;
            if(externalMath::getComponent(dir, scan) == 0)
                continue;
            double t = (externalMath::getComponent(point, scan) -
                        externalMath::getComponent(s, scan))/(externalMath::getComponent(dir, scan));
            holder.point = s + t*dir;

            QVector3D sN = normals[checkFace.normals[i]];
            QVector3D eN = normals[checkFace.normals[iNext]];
            holder.normal = sN + t*(eN - sN);

            bGo = false;
        }

    }

    return holder;
}

bool WireframeMesh::sphereTest(const QVector3D &origin, const QVector3D &dir)
{
    double value = sphereCenter.distanceToLine(origin, dir.normalized());

    if(value > radius)
        return false;

    return true;
}
