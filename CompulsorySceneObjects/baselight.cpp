#include "baselight.h"
#include "../worldinfo.h"
#include "../Model/ParametricSpheres/sphere.h"
#include "../externalmath.h"

#include <QDebug>

BaseLight::BaseLight(const lightInfo &props, Model *model): SceneObject(), lightModel(model), lightProperties(props)
{
    if(!model)
    {
        lightModel = new Sphere(props.position, props.color, 5);
    }
}

BaseLight::BaseLight(const lightInfo &&props, Model *model): SceneObject(), lightModel(model), lightProperties(props)
{
    if(!model)
    {
        lightModel = new Sphere(props.position, props.color, 5);
    }
}

BaseLight::~BaseLight()
{
    if(lightModel)
        delete lightModel;
}

rayTraceInfo BaseLight::intersect(const QVector3D &origin, const QVector3D &dir)
{
    if(lightModel)
        return lightModel->intersect(origin, dir);

    return rayTraceInfo();
}

const char *BaseLight::type() const
{
    return (typeid(BaseLight).name());
}

const char *BaseLight::type_s()
{
    return (typeid(BaseLight).name());
}

bool BaseLight::lightsPoint(const QVector3D &point)
{
    const double eps = 1e-3;
    WorldInfo &instance = WorldInfo::getInstance();
    QVector3D dir = point - lightProperties.position;
    double len = dir.length() - eps;
    dir.normalize();

    for(auto i : instance)
        if((*i).blocks(lightProperties.position, dir, len))
            return false;

    return true;
}

QVector3D BaseLight::getPosition() const
{
    return lightProperties.position;
}

QColor BaseLight::getColor() const
{
    return lightProperties.color;
}

float BaseLight::getIntensity() const
{
    return lightProperties.intensity;
}

QColor BaseLight::getLitResult(col color, const QVector3D &point) const
{
    double distanceSquared = (point - lightProperties.position).lengthSquared();
    color.r *= lightProperties.color.redF()*lightProperties.intensity/distanceSquared;
    color.g *= lightProperties.color.greenF()*lightProperties.intensity/distanceSquared;
    color.b *= lightProperties.color.blueF()*lightProperties.intensity/distanceSquared;

    QColor result;
    result.setRedF(externalMath::clamp(color.r, 0.f, 1.f));
    result.setGreenF(externalMath::clamp(color.g, 0.f, 1.f));
    result.setBlueF(externalMath::clamp(color.b, 0.f, 1.f));

    return result;
}
