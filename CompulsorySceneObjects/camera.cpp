#include <QThread>
#include <QDebug>
#include <QEventLoop>
#include <QApplication>
#include "../worldinfo.h"
#include "camera.h"
#include "../pointtransformations.h"
#include "../Renderer/raytracemultithreadrenderer.h"

Camera::Camera(QSize size, QSize resolution, Model *_cameraModel): SceneObject(),
    leftTop(0, -size.width()/2, size.height()/2), rightTop(0, size.width()/2, size.height()/2),
    leftBottom(0, -size.width()/2, -size.height()/2), origin(200, 0, 0),
    xRes(resolution.width()), yRes(resolution.height()), planeSize(size), cameraModel(_cameraModel),
    activeThreads(0), buf(nullptr), linesDrew(0)
{
}

Camera::~Camera()
{
    if(cameraModel)
        delete cameraModel;
}

rayTraceInfo Camera::intersect(const QVector3D &origin, const QVector3D &dir)
{
    if(cameraModel)
        return cameraModel->intersect(origin, dir);
    else
        return SceneObject::intersect(origin, dir);
}

QSize Camera::getSize()
{
    return planeSize;
}

void Camera::setFOV(double fov)
{
    setDistance(planeSize.width()/tan(fov/2));
}

void Camera::setDistance(double distance)
{
    QVector3D centerPoint = (rightTop + leftBottom)/2;
    QVector3D viewDirect = centerPoint - origin;
    QVector3D shift = viewDirect.normalized()*distance - viewDirect;

    leftBottom += shift;
    leftTop += shift;
    rightTop += shift;
}

void Camera::setDirection(const QVector3D &dir)
{
    QVector3D x(1, 0, 0);
    QVector3D y(0, 1, 0);
    QVector3D z(0, 0, 1);

    setDirection(float(transformations::getAngle(dir, x)), float(transformations::getAngle(dir, y)),
                 float(transformations::getAngle(dir, z)));
}

void Camera::setDirection(float roll, float pitch, float yaw)
{
    resetRotation();
    transformations::rotate(leftTop, origin, {roll, pitch, yaw});
    transformations::rotate(rightTop, origin, {roll, pitch, yaw});
    transformations::rotate(leftBottom, origin, {roll, pitch, yaw});
}

void Camera::setDirection(int roll, int pitch, int yaw)
{
    float degToRad = M_PI/180;
    setDirection(degToRad*roll, degToRad*pitch, degToRad*yaw);
}

void Camera::setOrigin(const QVector3D &newOrigin)
{
    QVector3D shift = newOrigin - origin;
    origin  = newOrigin;
    leftTop += shift;
    leftBottom += shift;
    rightTop += shift;
}

void Camera::setResolution(const QSize &newRes)
{
    xRes = newRes.width();
    yRes = newRes.height();
}

void Camera::setSize(const QSize &newSize)
{
    QVector3D xBasis = (rightTop - leftTop)/xRes;
    QVector3D yBasis = (leftBottom - leftTop)/yRes;
    QVector3D xCenter = (rightTop + leftTop)/2;
    QVector3D shiftX = xBasis*newSize.width()/2;

    leftTop = xCenter - shiftX;
    rightTop = xCenter + shiftX;
    leftBottom = leftTop + yBasis*newSize.height();

    planeSize = newSize;
}

void Camera::renderScene(QImage &img)
{
    buf = &img;
    int count = 1;//QThread::idealThreadCount() - 1;
    activeThreads = count;
    linesDrew = 0;

    QThread threads[count];
    RayTraceMultiThreadRenderer renderers[count];

    for(int i = 0; i < count; i++)
    {
        // Connect it all
        connect(threads + i, SIGNAL(started()), renderers + i, SLOT(start()));
        connect(renderers + i, SIGNAL(finished()), threads + i, SLOT(terminate()));
        connect(threads + i, SIGNAL(finished()), SLOT(threadDied()));
        connect(renderers + i, SIGNAL(lineRendered(QImage, int ,int)), SLOT(drawLine(QImage,int,int)));

        renderers[i].setOrigin(origin);
        renderers[i].setPlane(leftTop, rightTop, leftBottom);
        renderers[i].setRes(xRes, yRes);
        renderers[i].setStart(0, i);
        renderers[i].setSteps(1, count);

        renderers[i].moveToThread(threads + i);
        threads[i].start();
    }

    // Waiting for all threads to finish
    while(activeThreads)
    {
        QApplication::processEvents();
    }
}

void Camera::threadDied()
{
    activeThreads--;
}

void Camera::drawLine(QImage line, int _x, int y)
{
    for(int x = _x; x < buf->width(); x++)
        buf->setPixelColor(x, y, line.pixelColor(x, 0));

    emit drewLine(double(++linesDrew)/yRes);
}

QVector3D Camera::getDirection()
{
    return (leftBottom + rightTop)/2 - origin;
}

float Camera::getDistance()
{
    return getDirection().length();
}

QSize Camera::getResolution()
{
    return {xRes, yRes};
}

QVector3D Camera::getOrigin()
{
    return origin;
}

void Camera::resetRotation()
{
    float distance = getDistance();

    leftTop = {origin.x() - distance, origin.y() - planeSize.width()/2, origin.z() + planeSize.height()/2};
    rightTop = {origin.x() - distance, origin.y() + planeSize.width()/2, origin.z() + planeSize.height()/2};
    leftBottom = {origin.x() - distance, origin.y() - planeSize.width()/2, origin.z() - planeSize.height()/2};
}
