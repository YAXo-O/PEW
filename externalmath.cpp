#include <QVector2D>
#include <QVector3D>
#include <QColor>

#include "externalmath.h"
#include "pointtransformations.h"

QVector2D externalMath::doLinearSystem2of3(const QVector3D &a, const QVector3D &b, const QVector3D &value)
{
    if(a.x()*b.y() != b.x()*a.y())
        return doLinearSystem2of2({a.x(), a.y()}, {b.x(), b.y()}, {value.x(), value.y()});
    if(a.x()*b.z() != b.x()*a.z())
        return doLinearSystem2of2({a.x(), a.z()}, {b.x(), b.z()}, {value.x(), value.z()});
    if(a.y()*b.z() != b.y()*a.z())
        return doLinearSystem2of2({a.y(), a.z()}, {b.y(), b.z()}, {value.y(), value.z()});

    return {0, 0};
}

QVector2D externalMath::doLinearSystem2of3(const QVector3D &&a, const QVector3D &&b, const QVector3D &&value)
{
    return doLinearSystem2of3(a, b, value);
}

QVector2D externalMath::doLinearSystem2of2(const QVector2D &a, const QVector2D &b, const QVector2D &value)
{
    float d = a.x()*b.y() - a.y()*b.x();
    float d1 = value.x()*b.y() - value.y()*b.x();
    float d2 = a.x()*value.y() - a.y()*value.x();

    return {d1/d, d2/d};
}

QVector2D externalMath::doLinearSystem2of2(const QVector2D &&a, const QVector2D &&b, const QVector2D &&value)
{
    return doLinearSystem2of2(a, b, value);
}

double externalMath::getComponent(const QVector3D &vector, int component)
{
    switch(component)
    {
    case 0:
        return vector.x();

    case 1:
        return vector.y();

    case 2:
        return vector.z();

    default:
        return -1;
    }
}

QColor operator*(const QColor &color, double index)
{
    QColor result;
    result.setRedF(externalMath::clamp(color.redF()*index, 0.f, 1.f));
    result.setGreenF(externalMath::clamp(color.greenF()*index, 0.f, 1.f));
    result.setBlueF(externalMath::clamp(color.blueF()*index, 0.f, 1.f));

    return result;
}

QColor operator*(const QColor &colorA, const QColor &colorB)
{
    QColor result;
    result.setRedF(colorA.redF()*colorB.redF());
    result.setGreenF(colorA.greenF()*colorB.greenF());
    result.setBlueF(colorA.blueF()*colorB.blueF());

    return result;
}

QColor operator/(const QColor &color, double index)
{
    QColor result;
    result.setRedF(externalMath::clamp(color.redF()/index, 0.f, 1.f));
    result.setGreenF(externalMath::clamp(color.greenF()/index, 0.f, 1.f));
    result.setBlueF(externalMath::clamp(color.blueF()/index, 0.f, 1.f));

    return result;
}

QColor operator/(const QColor &colorA, const QColor &colorB)
{
    QColor result;
    result.setRedF(externalMath::clamp(colorA.redF()/colorB.redF(), 0.f, 1.f));
    result.setGreenF(externalMath::clamp(colorA.greenF()/colorB.greenF(), 0.f, 1.f));
    result.setBlueF(externalMath::clamp(colorA.blueF()/colorB.blueF(), 0.f, 1.f));

    return result;
}

bool externalMath::fuzzyCompare(const QVector3D &A, const QVector3D &B, double eps)
{
    if(fabs(A.x() - B.x()) < eps && fabs(A.y() - B.y()) < eps && fabs(A.z() - B.z()) < eps)
        return true;

    return false;
}

double externalMath::clamp(double value, double floor, double ceil)
{
    return value > ceil ? ceil : value < floor ? floor : value;
}

QColor &operator+=(QColor &colorA, const QColor &colorB)
{
    colorA.setRedF(externalMath::clamp(colorA.redF() + colorB.redF(), 0.f, 1.f));
    colorA.setGreenF(externalMath::clamp(colorA.greenF() + colorB.greenF(), 0.f, 1.f));
    colorA.setBlueF(externalMath::clamp(colorA.blueF() + colorB.blueF(), 0.f, 1.f));

    return colorA;
}

QColor &operator-=(QColor &colorA, const QColor &colorB)
{
    colorA.setRedF(externalMath::clamp(colorA.redF() - colorB.redF(), 0.f, 1.f));
    colorA.setGreenF(externalMath::clamp(colorA.greenF() - colorB.greenF(), 0.f, 1.f));
    colorA.setBlueF(externalMath::clamp(colorA.blueF() - colorB.blueF(), 0.f, 1.f));

    return colorA;
}

double externalMath::max(double value, double ceil)
{
    return value > ceil ? ceil : value;
}

double externalMath::min(double value, double floor)
{
    return value < floor ? floor : value;
}

QVector3D externalMath::getReflection(const QVector3D &normal, const QVector3D &lightDir)
{
    QVector3D n = normal.normalized();

    return lightDir - 2*n*QVector3D::dotProduct(n, lightDir);
}

QColor &operator*=(QColor &colorA, const QColor &colorB)
{
    colorA.setRedF(colorA.redF()*colorB.redF());
    colorA.setGreenF(colorA.greenF()*colorB.greenF());
    colorA.setBlueF(colorA.blueF()*colorB.blueF());

    return colorA;
}

intersection externalMath::raySegmentIntersection(const QVector3D &origin, const QVector3D &dir, const QVector3D &A, const QVector3D &B)
{
    QVector3D OA = A - origin;
    QVector3D BA = A - B;

    double left = OA.y()*(BA.z() - BA.x()) + OA.x()*(BA.z() + BA.y()) - OA.z()*(BA.x() + BA.y());
    double right = BA.y()*(dir.z() - dir.x()) - BA.z()*(dir.y() - dir.x()) + BA.x()*(dir.z() + dir.y());
    if(!right)
        return intersection();

    double t = -(left/right);
    intersection result;
    result.point = origin + dir*t;
    QVector3D PA = result.point - A;

    double s = -1;
    if(BA.x())
        s = PA.x()/BA.x();
    else if(BA.y())
        s = PA.y()/BA.y();
    else
        s = PA.z()/BA.z();

    if(s < 0 || s > 1)
        return intersection();

    result.bIntersects = true;

    return result;
}

float externalMath::doRaySegmentIntersect(const QVector3D &origin, const QVector3D &dir, const QVector3D &A, const QVector3D &B)
{
    const double eps = 1e-4;

    QVector3D AO = origin - A;
    QVector3D AB = B - A;

    QVector3D e1 = QVector3D::crossProduct(AO, AB);
    QVector3D e2 = QVector3D::crossProduct(AB, dir);
    // Ray points outwards?
    if(QVector3D::dotProduct(e1, e2) < -eps)
        return 0;

    double left = e1.length();
    double right = e2.length();
    if(!right)
    {
        // Colinear; Collide?
        QVector3D dn = dir.normalized();
        QVector3D AO = (origin - A).normalized();
        QVector3D BO = (origin - B).normalized();

        double a = QVector3D::dotProduct(dn, AO);
        double b = QVector3D::dotProduct(dn, BO);

        if(fabs(fabs(a) - 1) > eps || fabs(fabs(b) - 1) > eps || (a > 0 && b > 0))
            return 0.f;

        return 1.f;
    }

    double t = left/right;
    QVector3D point = origin + dir*t;
    QVector3D AP = point - A;

    double s = -1;
    if(fabs(AB.x()) > eps)
        s = AP.x()/AB.x();
    else if(fabs(AB.y()) > eps)
        s = AP.y()/AB.y();
    else
        s = AP.z()/AB.z();

    // Out of segment
    if(s < -eps || s > 1 + eps)
        return 0.f;

    // Origin lies on a segment
    if(t == 0)
        return 2.f;

    // Crosses vertex
    if( fabs(s) < eps || fabs(s - 1) < eps)
        return .5f;

    // Crosses
    return 1.f;
}
