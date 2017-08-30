#ifndef WIREFRAMEMESHINSTANCE_H
#define WIREFRAMEMESHINSTANCE_H

#include <QVector3D>
#include "wireframemesh.h"

class WireframeMeshInstance: public Model
{
    Q_OBJECT
public:
    WireframeMeshInstance(WireframeMesh *mesh = nullptr, QVector3D pivotPoint = {0, 0, 0});

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir);

    WireframeMesh *getMesh() const;
    void setMesh(WireframeMesh *value);

    QVector3D getPivotPoint() const;
    void setPivotPoint(const QVector3D &value);

    const char *type() const override;

private:
    QVector3D pivotPoint;
    // Transformation matrix should also be presented here
    WireframeMesh *mesh;

    bool bShowEdgedFaces;
    bool bShowVerticies;
    bool bShowSurface;
};

#endif // WIREFRAMEMESHINSTANCE_H
