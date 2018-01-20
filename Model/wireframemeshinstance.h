#ifndef WIREFRAMEMESHINSTANCE_H
#define WIREFRAMEMESHINSTANCE_H

#include <QVector3D>
#include "wireframemesh.h"
#include "material.h"
#include "../matrix.h"

class WireframeMeshInstance: public Model
{
    Q_OBJECT
public:
    WireframeMeshInstance(WireframeMesh *mesh = nullptr, QVector3D pivotPoint = {0, 0, 0});

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;
    bool blocks(const QVector3D &origin, const QVector3D &dir) override;
    bool blocks(const QVector3D &origin, const QVector3D &dir, const QVector3D &exclude) override;
    bool blocks(const QVector3D &origin, const QVector3D &dir, float maxDist) override;

    WireframeMesh *getMesh() const;
    void setMesh(WireframeMesh *value);

    QVector3D getPivotPoint() const;
    void setPivotPoint(const QVector3D &value);

    const char *type() const override;

    Material &material();

    void move(QVector3D shift) override;
    void rotate(QVector3D rotator) override;

protected:
    void pointToMeshSpace(QVector3D &point);
    void rayToMeshSpace(QVector3D &origin, QVector3D &dir);
    void pointFromMeshSpace(QVector3D &point);
    void rayFromMeshSpace(QVector3D &origin, QVector3D &dir);

private:
    QVector3D pivotPoint;
    // Transformation matrix should also be presented here
    WireframeMesh *mesh;
    Material mat;
    Matrix transforms; // World to mesh space
    Matrix reverseTransforms; // Mesh to world space

    bool bShowEdgedFaces;
    bool bShowVerticies;
    bool bShowSurface;
};

#endif // WIREFRAMEMESHINSTANCE_H
