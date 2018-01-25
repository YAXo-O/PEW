#include "particlesystem.h"

ParticleSystem::ParticleSystem(QWidget *parent): NodeData(parent), system(new QVector<Particle *>)
{
    visualPrepare("particlesystem");

    setDebugValue(QString::number(system->size()));
}

ParticleSystem::~ParticleSystem()
{
    for(auto i : *system)
        delete i;

    delete system;
}

bool ParticleSystem::isPresent() const
{
    return system != nullptr;
}

const void *ParticleSystem::getData()
{
    return system;
}

void ParticleSystem::setData(const void *newData)
{
    system = (QVector<Particle *> *)newData;
    setDebugValue(QString::number(system->size()));
}

const char *ParticleSystem::dataType() const
{
    return typeid(Particle).name();
}

const char *ParticleSystem::dataType_s()
{
    return typeid(Particle).name();
}

void ParticleSystem::resetMovable()
{
    for(auto i : *system)
        delete i;

    delete system;
    system = new QVector<Particle *>;
}
