#ifndef COLORMAP_H
#define COLORMAP_H

#include <QImage>
#include <QColor>

class ColorMap
{
public:
    ColorMap(const QColor &baseColor = Qt::black);
    ColorMap(const QColor &&baseColor);
    ColorMap(QImage *texture);
    ~ColorMap() = default;

    // All textures are stored outside of map, so this 'outside' has to delete them when necessary
    void setTexture(QImage *newTexture);
    void setBaseColor(const QColor &color);
    void setBaseColor(const QColor &&color);
    void setIndex(double index);

    QColor getMapColor(int x, int y);
    QColor getMapColor(double x, double y);
    QColor getMapColor(const QVector2D &uv);
    double getIndex() const;

private:
    QColor baseColor; // Color for map to be filled with(if no texture is present)
    QImage *texture; // Texture of the map
    double index; // Index of a map; Material decides what to do with it
};

#endif // COLORMAP_H
