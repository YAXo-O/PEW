#include "simpletestmodel.h"

SimpleTestModel::SimpleTestModel(QVector3D _center, double _radius): WireframeMesh(),
    radius(_radius), center(_center), col(Qt::red)
{
}

rayTraceInfo SimpleTestModel::intersect(const QVector3D &origin, const QVector3D &dir)
{
    if(center.distanceToLine(origin, dir) > radius)
        return rayTraceInfo();

    rayTraceInfo result;
    result.color = col;
    QVector3D central = (origin - center);
    double a2 = 2*dir.lengthSquared();
    double b = 2*(central.x()*dir.x() + central.y()*dir.y() + central.z()*dir.z());
    double c = central.lengthSquared() - pow(radius, 2);

    double d = sqrt(pow(b, 2) - 2*a2*c);
    double t1 = (-b+d)/(a2);
    double t2 = (-b-d)/(a2);

    double t = t1 < t2 ? t1 : t2;
    if(t < 0)
    {
        t = t1 > t2 ? t1 : t2;
        if(t2 < 0)
            return result;
    }

    result.bIntersects = true;
    result.param = t;

    return result;
}

double SimpleTestModel::getRadius() const
{
    return radius;
}

void SimpleTestModel::setRadius(double value)
{
    radius = value;
}

QVector3D SimpleTestModel::getCenter() const
{
    return center;
}

void SimpleTestModel::setCenter(const QVector3D &value)
{
    center = value;
}

QColor SimpleTestModel::getCol() const
{
    return col;
}

void SimpleTestModel::setCol(const QColor &value)
{
    col = value;
}

const char *SimpleTestModel::type() const
{
    return typeid(SimpleTestModel).name();
}
