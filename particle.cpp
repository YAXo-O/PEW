#include "particle.h"

Particle::Particle(SceneObject *m): model(m)
{

}

Particle::~Particle()
{
    for(auto i : attributes)
        delete i;
}

void Particle::addAttribute(const QString &name, void *value)
{
    attributes[name] = value;
}

bool Particle::checkAttribute(const QString &name) const
{
    return attributes.contains(name);
}

void *Particle::getAttribute(const QString &name)
{
    return attributes[name];
}
