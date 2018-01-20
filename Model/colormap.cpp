#include <QVector2D>
#include "colormap.h"

ColorMap::ColorMap(const QColor &_baseColor): baseColor(_baseColor), texture(nullptr), index(1)
{
}

ColorMap::ColorMap(const QColor &&_baseColor): baseColor(_baseColor), texture(nullptr), index(1)
{
}

ColorMap::ColorMap(QImage *_texture): baseColor(Qt::black), texture(_texture), index(1)
{
}

void ColorMap::setTexture(QImage *newTexture)
{
    texture = newTexture;
}

void ColorMap::setBaseColor(const QColor &color)
{
    baseColor = color;
}

void ColorMap::setBaseColor(const QColor &&color)
{
    setBaseColor(color);
}

void ColorMap::setIndex(double _index)
{
    index = _index;
}

QColor ColorMap::getMapColor(int x, int y)
{
    if(texture && x < texture->width() && y < texture->height())
        return texture->pixelColor(x, y);

    return baseColor;
}

QColor ColorMap::getMapColor(double x, double y)
{
    if(texture)
        return texture->pixelColor((texture->width()-1)*x, (texture->height()-1)*(1-y));

    return baseColor;
}

QColor ColorMap::getMapColor(const QVector2D &uv)
{
    return getMapColor(uv.x(), uv.y());
}

double ColorMap::getIndex() const
{
    return index;
}
