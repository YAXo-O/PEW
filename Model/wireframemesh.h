#ifndef WIREFRAMEMESH_H
#define WIREFRAMEMESH_H

#include "model.h"

class WireframeMesh : public Model
{
    Q_OBJECT
public:
    WireframeMesh();
    ~WireframeMesh() {}

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;
    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir, bool bEdgedFaces,
                           bool bVerticies, bool bSurface);

    void addVertex(const QVector3D &vertex);
    void addVertex(const QVector3D &&vertex);
    void addUniqueVertex(const QVector3D &vertex);
    void addUniqueVertex(const QVector3D &&vertex);

    void addFace();
    void addFaceVertex(const QVector3D &vertex);
    void addFaceVertex(const QVector3D &&vertex);
    void addFaceVertex(size_t id);
    void addFaceColor(const QColor &col);
    void addFaceColor(const QColor &&col);
    void faceNormal();
    void reverseNormal();
    void setVisible(bool visible);

    const char *type() const override;

protected:
    QVector<QVector3D> verticies;
    QVector<face> faces;

    bool sphereTest(const QVector3D &origin, const QVector3D &dir, const QVector3D &center, double radius);
    void getSphere(QVector3D &center, double &radius);
};

#endif // WIREFRAMEMESH_H
