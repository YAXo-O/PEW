#ifndef WIREFRAMEMESH_H
#define WIREFRAMEMESH_H

#include "model.h"
#include "material.h"

class QVector2D;

enum scanAxes
{
    SA_X = 0,
    SA_Y = 1,
    SA_Z = 2
};

struct uvLoopHolder
{
    QVector3D point;
    QVector2D uv;
    bool bVertex = false;
};

struct normalLoopHolder
{
    QVector3D point;
    QVector3D normal;
    bool bVertex = false;
};

class WireframeMesh : public Model
{
    Q_OBJECT
public:
    WireframeMesh();
    ~WireframeMesh();

    traceIntersectInfo trace(const QVector3D &origin, const QVector3D &dir);

    bool blocks(const QVector3D &origin, const QVector3D &dir) override;
    bool blocks(const QVector3D &origin, const QVector3D &dir, const QVector3D &exclude) override;
    bool blocks(const QVector3D &origin, const QVector3D &dir, float maxDist) override;

    void addVertex(const QVector3D &vertex);
    void addVertex(const QVector3D &&vertex);
    void addNormal(const QVector3D &normal);
    void addNormal(const QVector3D &&normal);
    void addTextureCoordinate(float u, float v);

    void addFace();
    void appendVertex(size_t id);
    void appendNormal(size_t id);
    void appendTextureCoordinate(size_t id);

    void prepareMesh();

    const char *type() const override;

protected:
    QVector<QVector3D> verticies;
    QVector<QVector3D> normals;
    QVector<QVector2D> uvs;
    QVector<face> faces;

    QVector3D sphereCenter;
    double radius;

    bool sphereTest(const QVector3D &origin, const QVector3D &dir);
    void getSphere();
    traceIntersectInfo findIntersection(const QVector3D &origin, const QVector3D &dir);
    bool isFacing(const QVector3D &dir, const face &curFace);
    bool onFace(const QVector3D &point, const face &face);

private:
    bool crossProductCheck(const QVector3D &point, const face &checkFace);
    bool rayCheck(const QVector3D &point, const face &checkFace);
    QVector2D findUv(const QVector3D &point, const face &checkFace, scanAxes axes);
    QVector3D findNormal(const QVector3D &point, const face &checkFace, scanAxes axes);
    uvLoopHolder uvLoop(const QVector3D &point, const face &checkFace, scanAxes scan, int &i);
    normalLoopHolder normalLoop(const QVector3D &point, const face &checkFace ,scanAxes scan, int &i);
};

#endif // WIREFRAMEMESH_H
