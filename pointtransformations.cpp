#include <cmath>
#include "pointtransformations.h"
#include "matrix.h"

void shift(QVector3D &origin, const QVector3D &shift)
{
    origin += shift;
}

void rotateX(QVector3D &point, double angle)
{
    Matrix transf(4, 4);
    transf.loadIdentity();

    double sina = sin(angle);
    double cosa = cos(angle);

    transf.at(1, 1) = cosa;
    transf.at(2, 1) = sina;
    transf.at(1, 2) = -sina;
    transf.at(2, 2) = cosa;

    point = (Matrix(point)*transf).toVector();
}

void rotateY(QVector3D &point, double angle)
{
    Matrix transf(4, 4);
    transf.loadIdentity();

    double sina = sin(angle);
    double cosa = cos(angle);

    transf.at(0, 0) = cosa;
    transf.at(0, 2) = -sina;
    transf.at(2, 0) = sina;
    transf.at(2, 2) = cosa;

    point = (Matrix(point)*transf).toVector();
}

void rotateZ(QVector3D &point, double angle)
{
    Matrix transf(4, 4);
    transf.loadIdentity();

    double sina = sin(angle);
    double cosa = cos(angle);

    transf.at(0, 0) = cosa;
    transf.at(0, 1) = sina;
    transf.at(1, 0) = -sina;
    transf.at(1, 1) = cosa;

    point = (Matrix(point)*transf).toVector();
}

void rotate(QVector3D &origin, const QVector3D &pivotPoint, const QVector3D &rotator)
{
    if(rotator.x())
    {
        shift(origin, -pivotPoint);
        rotateX(origin, rotator.x());
        shift(origin, pivotPoint);
    }

    if(rotator.y())
    {
        shift(origin, -pivotPoint);
        rotateY(origin, rotator.y());
        shift(origin, pivotPoint);
    }

    if(rotator.z())
    {
        shift(origin, -pivotPoint);
        rotateZ(origin, rotator.z());
        shift(origin, pivotPoint);
    }
}

void scale(QVector3D &origin, const QVector3D &pivotPoint, const QVector3D &scale)
{
    QVector3D dir = origin - pivotPoint;

    dir *= scale.x();
    dir *= scale.y();
    dir *= scale.z();

    origin = dir + pivotPoint;
}

double getAngleCos(const QVector3D &a, const QVector3D &b)
{
    return QVector3D::dotProduct(a, b)/(a.length()*b.length());
}

double getAngle(const QVector3D &a, const QVector3D &b)
{
    return acos(getAngleCos(a, b));
}
