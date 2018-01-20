#ifndef EXTERNALMATH_H
#define EXTERNALMATH_H

class QVector2D;
class QColor;

#include <QVector3D>

struct intersection
{
    QVector3D point;
    bool bIntersects = false;
};

QColor operator*(const QColor &color, double index);
QColor operator*(const QColor &colorA, const QColor &colorB);
QColor operator/(const QColor &color, double index);
QColor operator/(const QColor &colorA, const QColor &colorB);
QColor &operator+=(QColor &colorA, const QColor &colorB);
QColor &operator-=(QColor &colorA, const QColor &colorB);
QColor &operator*=(QColor &colorA, const QColor &colorB);

namespace externalMath
{
    const QVector3D nullVector = {0, 0, 0};

    // doLinearSystemNofX - Finds roots for linear system of n equations with x variables
    QVector2D doLinearSystem2of3(const QVector3D &a, const QVector3D &b, const QVector3D &value);
    QVector2D doLinearSystem2of3(const QVector3D &&a, const QVector3D &&b, const QVector3D &&value);
    QVector2D doLinearSystem2of2(const QVector2D &a, const QVector2D &b, const QVector2D &value);
    QVector2D doLinearSystem2of2(const QVector2D &&a, const QVector2D &&b, const QVector2D &&value);

    double getComponent(const QVector3D &vector, int component);
    double clamp(double value, double floor, double ceil);
    double max(double value, double ceil);
    double min(double value, double floor);

    bool fuzzyCompare(const QVector3D &A, const QVector3D &B, double eps);

    QVector3D getReflection(const QVector3D &normal, const QVector3D &lightDir);

    intersection raySegmentIntersection(const QVector3D &origin, const QVector3D &dir, const QVector3D &A, const QVector3D &B);
    // 0 - no intersection; .5 - intersects vertex, 1 - intersects segment, 2 - origin lies on segment
    float doRaySegmentIntersect(const QVector3D &origin, const QVector3D &dir, const QVector3D &A, const QVector3D &B);
}


#endif // EXTERNALMATH_H
