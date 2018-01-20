#include <cmath>
#include "pointtransformations.h"
#include "matrix.h"

void transformations::shift(QVector3D &origin, const QVector3D &shift)
{
    origin += shift;
}

void transformations::rotateX(QVector3D &point, double angle)
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

void transformations::rotateY(QVector3D &point, double angle)
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

void transformations::rotateZ(QVector3D &point, double angle)
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

void transformations::rotate(QVector3D &origin, const QVector3D &pivotPoint, const QVector3D &rotator)
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

void transformations::scale(QVector3D &origin, const QVector3D &pivotPoint, const QVector3D &scale)
{
    QVector3D dir = origin - pivotPoint;

    dir *= scale.x();
    dir *= scale.y();
    dir *= scale.z();

    origin = dir + pivotPoint;
}

double transformations::getAngleCos(const QVector3D &a, const QVector3D &b)
{
    return QVector3D::dotProduct(a, b)/(a.length()*b.length());
}

double transformations::getAngle(const QVector3D &a, const QVector3D &b)
{
    return acos(getAngleCos(a, b));
}

Matrix transformations::rotationMatrix(const QVector3D &rotator)
{
    Matrix result(4, 4);
    result.loadIdentity();

    if(rotator.x())
    {
        double sina = sin(rotator.x());
        double cosa = cos(rotator.x());

        result.at(1, 1) = cosa;
        result.at(2, 1) = sina;
        result.at(1, 2) = -sina;
        result.at(2, 2) = cosa;
    }
    if(rotator.y())
    {
        Matrix transf(4, 4);
        transf.loadIdentity();

        double sina = sin(rotator.y());
        double cosa = cos(rotator.y());

        transf.at(0, 0) = cosa;
        transf.at(0, 2) = -sina;
        transf.at(2, 0) = sina;
        transf.at(2, 2) = cosa;

        result *= transf;
    }
    if(rotator.z())
    {
        Matrix transf(4, 4);
        transf.loadIdentity();

        double sina = sin(rotator.z());
        double cosa = cos(rotator.z());

        transf.at(0, 0) = cosa;
        transf.at(0, 1) = sina;
        transf.at(1, 0) = -sina;
        transf.at(1, 1) = cosa;

        result *= transf;
    }

    return result;
}

Matrix transformations::moveMatrix(const QVector3D &shift)
{
    Matrix transf(4, 4);
    transf.loadIdentity();

    transf.at(0, 3) = shift.x();
    transf.at(1, 3) = shift.y();
    transf.at(2, 3) = shift.z();

    return transf;
}
