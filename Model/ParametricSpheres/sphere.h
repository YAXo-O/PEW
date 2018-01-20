#ifndef SPHERE_H
#define SPHERE_H

#include <QObject>
#include <QVector3D>
#include <QColor>

#include "../model.h"

class Sphere : public Model
{
    Q_OBJECT
public:
    Sphere(QVector3D position, QColor color, double radius);
    ~Sphere() {}

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;
    const char *type() const override;

    void setColor(const QColor &color);
    void setColor(const QColor &&color);
    const QColor &getColor() const;

    const QVector3D &getPosition() const;
    void setPosition(const QVector3D &value);
    void setPosition(const QVector3D &&value);

    double getRadius() const;
    void setRadius(double value);

    void move(QVector3D shift) override;

private:
    QVector3D position;
    QColor color;
    double radius;
};

#endif // SPHERE_H
