#include "sphere.h"

Sphere::Sphere(QVector3D _position, QColor _color, double _radius): Model(), position(_position), color(_color), radius(_radius)
{
}

rayTraceInfo Sphere::intersect(const QVector3D &origin, const QVector3D &dir)
{
    if(position.distanceToLine(origin, dir.normalized()) > radius)
        return rayTraceInfo();

    rayTraceInfo result;
    result.bIntersects = true;
    result.param = 1;
    result.color = color;

    return result;
}

const char *Sphere::type() const
{
    return typeid(Sphere).name();
}

void Sphere::setColor(const QColor &_color)
{
    color = _color;
}

void Sphere::setColor(const QColor &&_color)
{
    color = _color;
}

const QColor &Sphere::getColor() const
{
    return color;
}

const QVector3D &Sphere::getPosition() const
{
    return position;
}

void Sphere::setPosition(const QVector3D &value)
{
    position = value;
}

void Sphere::setPosition(const QVector3D &&value)
{
    position = value;
}

double Sphere::getRadius() const
{
    return radius;
}

void Sphere::setRadius(double value)
{
    radius = value;
}

void Sphere::move(QVector3D shift)
{
    position += shift;
}
