#ifndef SIMPLETESTMODEL_H
#define SIMPLETESTMODEL_H

#include "wireframemesh.h"

class SimpleTestModel: public WireframeMesh
{
    Q_OBJECT
public:
    SimpleTestModel(QVector3D center = {0, 0, 0}, double radius = 100);
    ~SimpleTestModel() {}

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;

    double getRadius() const;
    void setRadius(double value);

    QVector3D getCenter() const;
    void setCenter(const QVector3D &value);

    QColor getCol() const;
    void setCol(const QColor &value);

    const char *type() const override;

private:
    double radius;
    QVector3D center;
    QColor col;
};

#endif // SIMPLETESTMODEL_H
