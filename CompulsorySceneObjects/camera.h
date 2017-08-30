#ifndef CAMERA_H
#define CAMERA_H

#include <QSize>
#include "../sceneobject.h"
#include "../Model/model.h"

class Camera : public SceneObject
{
    Q_OBJECT

public:
    Camera(QSize size, QSize resolution, Model *cameraModel = nullptr);
    ~Camera();

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;

    QVector3D getDirection();
    float getDistance();
    QSize getResolution();
    QVector3D getOrigin();
    QSize getSize();

public slots:
    void setDistance(double distance); // distance from origin to projection plane
    void setDirection(const QVector3D &dir); // direction, in which camera is oriented
    void setDirection(float roll, float pitch, float yaw);
    void setOrigin(const QVector3D &newOrigin);
    void setResolution(const QSize &newRes);
    void setSize(const QSize &newSize);
    void renderScene(QImage &img);

protected:
    QVector3D leftTop, rightTop, leftBottom; // Point of our projection plane
    QVector3D origin; // Point, from which we observe the world
    int xRes, yRes; // Screen resolution, required for tracing
    QSize planeSize; // Sizes, better keep them in order not to recalculate every time

    // Visual representation; For rendering from other cameras
    Model *cameraModel;

    void resetRotation();

};

#endif // CAMERA_H
