#include <QPainter>
#include <QDebug>
#include "../worldinfo.h"
#include "camera.h"
#include "../pointtransformations.h"

#define SHOW_STAT

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

    setDirection(getAngle(dir, x), getAngle(dir, y), getAngle(dir, z));
}

void Camera::setDirection(float roll, float pitch, float yaw)
{
    resetRotation();
    rotate(leftTop, origin, {roll, pitch, yaw});
    rotate(rightTop, origin, {roll, pitch, yaw});
    rotate(leftBottom, origin, {roll, pitch, yaw});
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
    //QVector3D yCenter = (leftBottom + leftTop)/2;
    QVector3D shiftX = xBasis*newSize.width()/2;
    //QVector3D shiftY = yBasis*newSize.height()/2;

    leftTop = xCenter - shiftX;// + yCenter + shiftY;
    rightTop = xCenter + shiftX;// + yCenter + shiftY;
    leftBottom = leftTop + yBasis*newSize.height();

    planeSize = newSize;
}

void Camera::renderScene(QImage &img)
{
    img.fill(Qt::darkGray);
    QPainter p(&img);

    for(int x = 0; x < xRes; x++)
    {
        QVector3D xBasis = (rightTop - leftTop)/xRes;
        for(int y = 0; y < yRes; y++)
        {
            QVector3D yBasis = (leftBottom - leftTop)/yRes;
            QVector3D planePoint = (xBasis*x + yBasis*y + leftTop);
            QVector3D rayDirection = (planePoint - origin).normalized();

            rayTraceInfo closestIntersection;
            WorldInfo &wi = WorldInfo::getInstance();

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
        }
    }

#ifdef SHOW_STAT
    QVector3D dir = getDirection();

    int lineHeight = 10;
    p.setPen(Qt::yellow);
    p.drawText(0, lineHeight, "Origin: (" + QString::number(origin.x()) + "; " + QString::number(origin.y()) + "; "
               + QString::number(origin.z()) + ")");
    p.drawText(0, lineHeight*2, "Direction: (" + QString::number(dir.x()) + "; " + QString::number(dir.y())
               + "; " + QString::number(dir.z()) + ")");
    p.drawText(0, lineHeight*3, "Distance: " + QString::number(dir.length()));

    int lineLen = 100;
    QPoint offset(lineLen/2, img.height()/2);
    QPoint offset2(lineLen/2, offset.y() + lineLen);
    QPoint offset3(lineLen/2, offset2.y() + lineLen);
    dir.normalize();
    dir *= lineLen;

    // Drawing axes
    p.drawText(0, offset.y()-offset.x(), "XoY");
    p.drawText(0, offset2.y()-offset.x(), "XoZ");
    p.drawText(0, offset3.y()-offset.x(), "YoZ");
    p.drawLine(0, offset.y(), offset.x()*2, offset.y());
    p.drawLine(offset.x(), offset.y() + offset.x(), offset.x(),  offset.y() - offset.x());
    p.drawLine(0, offset2.y(), offset2.x()*2, offset2.y());
    p.drawLine(offset2.x(), offset2.y() + offset2.x(), offset2.x(),  offset2.y() - offset2.x());
    p.drawLine(0, offset3.y(), offset3.x()*2, offset3.y());
    p.drawLine(offset3.x(), offset3.y() + offset3.x(), offset3.x(),  offset3.y() - offset3.x());
    // Drawing Vector
    p.setPen(Qt::darkRed);
    p.drawLine(offset.x(), offset.y(), offset.x() + dir.x(), offset.y() + dir.y());
    p.drawLine(offset2.x(), offset2.y(), offset2.x() + dir.x(), offset2.y() + dir.z());
    p.drawLine(offset3.x(), offset3.y(), offset3.x() + dir.y(), offset3.y() + dir.z());
#endif

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
