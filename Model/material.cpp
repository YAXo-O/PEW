#include "material.h"
#include "../worldinfo.h"
#include "../externalmath.h"

#include <QDebug>

Material::Material(): ambient(Qt::gray), diffuse(Qt::gray), specularColor(Qt::white), specularLevel(Qt::white)
{
    ambient.setIndex(5e-2);
    diffuse.setIndex(1);
    specularColor.setIndex(1);
    specularLevel.setIndex(10);
}

ColorMap &Material::getAmbient()
{
    return ambient;
}

ColorMap &Material::getDiffuse()
{
    return diffuse;
}

ColorMap &Material::getSpecularColor()
{
    return specularColor;
}

ColorMap &Material::getSpecularLevel()
{
    return specularLevel;
}

const ColorMap &Material::getAmbient() const
{
    return ambient;
}

const ColorMap &Material::getDiffuse() const
{
    return diffuse;
}

const ColorMap &Material::getSpecularColor() const
{
    return specularColor;
}

const ColorMap &Material::getSpecularLevel() const
{
    return specularLevel;
}

QColor Material::getColor(traceIntersectInfo &info, const QVector3D &)
{
    WorldInfo &instance = WorldInfo::getInstance();
    QColor color = ambient.getMapColor(info.uvs)*ambient.getIndex();

    QColor materialDiffuseColor = Qt::black;
    QColor materialSpecularColor = Qt::black;

    QColor diffuseColor = diffuse.getMapColor(info.uvs)*diffuse.getIndex();
    QColor specular = specularColor.getMapColor(info.uvs)*specularColor.getIndex();
    double specularLevelValue = specularLevel.getMapColor(info.uvs).lightnessF()*specularLevel.getIndex();

    // Lightning
    for(auto light = instance.beginLights(); light != instance.endLights(); light++)
    {
        QVector3D lightPos = (*light)->getPosition();
        QVector3D direction = lightPos - info.intersection;
        direction.normalize();

        // Diffuse
        double cosThetta = externalMath::clamp(QVector3D::dotProduct(info.normal, direction), 0.f, 1.f);
        QColor currentDiffuse = (*light)->getLitResult(
        {diffuseColor.redF()*cosThetta, diffuseColor.greenF()*cosThetta, diffuseColor.blueF()*cosThetta},
                    info.intersection);

        //Specular
        double cosAlpha = externalMath::clamp(
                    QVector3D::dotProduct(info.normal, externalMath::getReflection(info.normal, -direction)), 0.f, 1.f);
        double specFactor = pow(cosAlpha, specularLevelValue);
        QColor currentSpecular = (*light)->getLitResult(
        {specular.redF()*specFactor, specular.greenF()*specFactor, specular.blueF()*specFactor}, info.intersection);

        if((*light)->lightsPoint(info.intersection))
        {
            materialDiffuseColor += currentDiffuse;
            materialSpecularColor += currentSpecular;
        }

    }

    color += materialDiffuseColor;
    color += materialSpecularColor;

    return color;
}
