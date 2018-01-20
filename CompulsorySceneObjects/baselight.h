#ifndef BASELIGHT_H
#define BASELIGHT_H

#include <QColor>
#include <QVector3D>
#include "../sceneobject.h"
#include "../Model/model.h"
#include "lightinfo.h"

struct col
{
    double r, g, b;
};

class BaseLight: public SceneObject
{
    Q_OBJECT
public:
    BaseLight(const lightInfo &props, Model *model = nullptr);
    BaseLight(const lightInfo &&props, Model *model = nullptr);
    ~BaseLight();

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;
    const char *type() const override;
    static const char *type_s();

    virtual bool lightsPoint(const QVector3D &point); // Baselight lights up evertything non-blocked

    QVector3D getPosition() const;
    QColor getColor() const;
    float getIntensity() const;
    virtual QColor getLitResult(col color, const QVector3D &point) const; // Light specific intensity

private:
    Model *lightModel;
    lightInfo lightProperties;
};

#endif // BASELIGHT_H
