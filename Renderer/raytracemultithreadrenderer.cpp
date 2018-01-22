#include <QPainter>
#include <QImage>
#include <QDebug>

#include "raytracemultithreadrenderer.h"
#include "../worldinfo.h"
#include "../tracinginfo.h"

RayTraceMultiThreadRenderer::RayTraceMultiThreadRenderer(QObject *parent): Renderer(parent)
{
}

void RayTraceMultiThreadRenderer::setSteps(int _xStep, int _yStep)
{
    xStep = _xStep;
    yStep = _yStep;
}

void RayTraceMultiThreadRenderer::setStart(int _xStart, int _yStart)
{
    xStart = _xStart;
    yStart = _yStart;
}

void RayTraceMultiThreadRenderer::setRes(int _xRes, int _yRes)
{
    xRes = _xRes;
    yRes = _yRes;
}

void RayTraceMultiThreadRenderer::setPlane(const QVector3D &_leftTop,
                                           const QVector3D &_rightTop, const QVector3D &_leftBottom)
{
    leftTop = _leftTop;
    rightTop = _rightTop;
    leftBottom = _leftBottom;
}

void RayTraceMultiThreadRenderer::setOrigin(const QVector3D &_origin)
{
    origin = _origin;
}

void RayTraceMultiThreadRenderer::start()
{
    QImage img = QImage(xRes, 1, QImage::Format_RGB32);

    QVector3D xBasis = (rightTop - leftTop)/xRes;
    QVector3D yBasis = (leftBottom - leftTop)/yRes;
    WorldInfo &wi = WorldInfo::getInstance();
    rayTraceInfo closestIntersection;

    for(int y = yStart; y < yRes; y += yStep)
    {
        for(int x = xStart; x < xRes; x += xStep)
        {
            QVector3D planePoint = (xBasis*x + yBasis*y + leftTop);
            QVector3D rayDirection = (planePoint - origin);
            closestIntersection.bIntersects = false;

            //for(auto i = wi.begin(); i != wi.end(); i++)
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
                img.setPixelColor(x, 0, closestIntersection.color);
            else
                img.setPixelColor(x, 0, Qt::gray);
        }
        emit lineRendered(img, 0, y);
    }

    emit finished();
}
