#ifndef PARTICLE_H
#define PARTICLE_H

#include <QMap>
#include "Model/model.h"

class Particle
{
public:
    Particle(SceneObject *m);
    ~Particle();

    void addAttribute(const QString &name, void *value);
    bool checkAttribute(const QString &name) const;
    void *getAttribute(const QString &name);

    void setModel(SceneObject *m);
    Model *getModel;

private:
    QMap<QString, void *> attributes;
    SceneObject *model;
};

#endif // PARTICLE_H
