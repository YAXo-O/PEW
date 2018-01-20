#include <QPainter>
#include <QDebug>
#include "../worldinfo.h"
#include "camera.h"
#include "../pointtransformations.h"

Camera::Camera(QSize size, QSize resolution, Model *_cameraModel): SceneObject(),
    leftTop(0, -size.width()/2, size.height()/2), rightTop(0, size.width()/2, size.height()/2),
    leftBottom(0, -size.width()/2, -size.height()/2), origin(200, 0, 0),
    xRes(resolution.width()), yRes(resolution.height()), planeSize(size), cameraModel(_cameraModel)
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
    QPainter p(&img);

    QVector3D xBasis = (rightTop - leftTop)/xRes;
    QVector3D yBasis = (leftBottom - leftTop)/yRes;
    WorldInfo &wi = WorldInfo::getInstance();
    rayTraceInfo closestIntersection;

    for(int x = 0; x < xRes; x++)
    {
        for(int y = 0; y < yRes; y++)
        {
            QVector3D planePoint = (xBasis*x + yBasis*y + leftTop);
            QVector3D rayDirection = (planePoint - origin);
            closestIntersection.bIntersects = false;

            for(auto i:wi)
            {
                rayTraceInfo intersection = i->intersect(origin, rayDirection);
                if(intersection.bIntersects)
                {
                    if(closestIntersection.bIntersects == false || closestIntersection.param > intersection.param)
                        closestIntersection = intersection;
                }
            }

            if(closestIntersection.bIntersects)
            {
                p.setPen(closestIntersection.color);
                p.drawPoint(x, y);
            }
            else
            {
                p.setPen(Qt::darkGray);
                p.drawPoint(x, y);
            }
        }
    }

    p.end();
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
