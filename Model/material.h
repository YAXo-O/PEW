#ifndef MATERIAL_H
#define MATERIAL_H

#include "colormap.h"
#include "../tracinginfo.h"

class Material
{
public:
    Material();
    ~Material() = default;

    ColorMap &getAmbient();
    ColorMap &getDiffuse();
    ColorMap &getSpecularColor();
    ColorMap &getSpecularLevel();

    const ColorMap &getAmbient() const;
    const ColorMap &getDiffuse() const;
    const ColorMap &getSpecularColor() const;
    const ColorMap &getSpecularLevel() const;

    QColor getColor(traceIntersectInfo &surfaceInfo, const QVector3D &viewDir);

private:
    ColorMap ambient;
    ColorMap diffuse;
    ColorMap specularColor;
    ColorMap specularLevel;
};

#endif // MATERIAL_H
