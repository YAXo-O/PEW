#ifndef MODEL_H
#define MODEL_H

#include "../sceneobject.h"
#include "modelinfo.h"

class Model : public SceneObject
{
    Q_OBJECT
public:
    Model();
    ~Model() {}

    rayTraceInfo intersect(const QVector3D &origin, const QVector3D &dir) override;
    const char *type() const override;

};

#endif // MODEL_H
