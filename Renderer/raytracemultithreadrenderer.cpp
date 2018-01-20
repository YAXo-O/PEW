#include <QPainter>
#include <QImage>

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
    QPainter p(&img);

    QVector3D xBasis = (rightTop - leftTop)/xRes*xStep;
    QVector3D yBasis = (leftBottom - leftTop)/yRes*yStep;
    WorldInfo &wi = WorldInfo::getInstance();
    rayTraceInfo closestIntersection;

    for(int y = yStart; y < yRes; y++)
    {
        for(int x = xStart; x < xRes; x++)
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
                p.drawPoint(x, 0);
            }
        }
        emit lineRendered(img, 0, y);
    }

    p.end();
}
