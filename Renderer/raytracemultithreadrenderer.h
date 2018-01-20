#ifndef RAYTRACEMULTITHREADRENDERER_H
#define RAYTRACEMULTITHREADRENDERER_H

#include <QVector3D>
#include <QImage>

#include "renderer.h"

class RayTraceMultiThreadRenderer : public Renderer
{
    Q_OBJECT

    explicit RayTraceMultiThreadRenderer(QObject *parent = nullptr);
    virtual ~RayTraceMultiThreadRenderer() {}

    void setBuffer(QImage *buf);
    void setSteps(int xStep, int yStep);
    void setStart(int xStart, int yStart);
    void setRes(int xRes, int yRes);
    void setPlane(const QVector3D &leftTop, const QVector3D &rightTop, const QVector3D &leftBottom);
    void setOrigin(const QVector3D &origin);

public slots:
    void start() override;

signals:
    void finished();
    void lineRendered(QImage line, int x, int y);

private:
    int xStep, yStep;
    int xStart, yStart;
    int xRes, yRes;
    QVector3D leftTop, rightTop, leftBottom;
    QVector3D origin;
};

#endif // RAYTRACEMULTITHREADRENDERER_H
