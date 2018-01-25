#ifndef CREATEPARTICLESYSTEM_H
#define CREATEPARTICLESYSTEM_H

#include "../basenode.h"
#include "../externalvariable.h"
#include "../NodesWidgets/createparticlesystemcontainer.h"

class CreateParticleSystem : public BaseNode
{
    Q_OBJECT
public:
    explicit CreateParticleSystem(QString nodeName = "Create Particle System", QWidget *parent = nullptr);
    virtual ~CreateParticleSystem() {}

public slots:
    void enable(BaseNode *caller) override;

private:
    ExternalVariable *array;
    ExternalVariable *particleSystem;

    CreateParticleSystemContainer *wid;
};

#endif // CREATEPARTICLESYSTEM_H
