#include "createparticlesystemcontainer.h"

CreateParticleSystemContainer::CreateParticleSystemContainer(CreateParticleSystemWidget *paramsPanel):
    NodeParamsContainer(paramsPanel)
{
}

const void *CreateParticleSystemContainer::getValue()
{
    CreateParticleSystemWidget *wid = (CreateParticleSystemWidget *)getParamsPanel();
    if(wid)
    {
        data.pos = wid->getPos();
        data.count = wid->getCount();
        data.rad = wid->getRadius();

        return &data;
    }

    return nullptr;
}
