#ifndef CREATEPARTICLESYSTEMCONTAINER_H
#define CREATEPARTICLESYSTEMCONTAINER_H

#include <QVector3D>

#include "../nodeparamscontainer.h"
#include "./createparticlesystemwidget.h"

struct psCreate
{
    QVector3D pos;
    double rad;
    unsigned count;
};

class CreateParticleSystemContainer : public NodeParamsContainer
{
public:
    CreateParticleSystemContainer(CreateParticleSystemWidget *paramsPanel);
    ~CreateParticleSystemContainer() {}

    const void *getValue() override;

private:
    psCreate data;
};


#endif // CREATEPARTICLESYSTEMCONTAINER_H
