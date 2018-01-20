#ifndef POINTTRANSFORMATIONS_H
#define POINTTRANSFORMATIONS_H

#include <QVector3D>
class Matrix;

namespace transformations
{
    void shift(QVector3D &origin, const QVector3D &shift);
    void rotate(QVector3D &origin, const QVector3D &pivotPoint, const QVector3D &rotator); // roll pitch yaw
    void rotateX(QVector3D &point, double angle);
    void rotateY(QVector3D &point, double angle);
    void rotateZ(QVector3D &point, double angle);
    Matrix rotationMatrix(const QVector3D &rotator);
    Matrix moveMatrix(const QVector3D &shift);
    void scale(QVector3D &origin, const QVector3D &pivotPoint, const QVector3D &scale);
    double getAngleCos(const QVector3D &a, const QVector3D &b);
    double getAngle(const QVector3D &a, const QVector3D &b);
}

#endif // POINTTRANSFORMATIONS_H
